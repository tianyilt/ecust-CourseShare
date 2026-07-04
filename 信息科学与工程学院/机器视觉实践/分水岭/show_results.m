function show_results()
% show_results() - display original image, segmentation overlay and intermediate
% images produced by watershed_segmentation.py. Provides an interactive
% alpha slider and a Save button. All UI text is in English to avoid encoding issues.

% Determine output folder relative to this file
scriptDir = fileparts(mfilename('fullpath'));
outDirBase = fullfile(scriptDir, 'output');

% Find the most recent subdirectory in output/
if ~exist(outDirBase, 'dir')
    error('Output directory %s does not exist. Please run the Python script first.', outDirBase);
end

subDirs = dir(outDirBase);
subDirs = subDirs([subDirs.isdir] & ~ismember({subDirs.name}, {'.', '..'}));
if isempty(subDirs)
    error('No subdirectories found in %s. Please run the Python script first.', outDirBase);
end

% Sort by date modified, take the most recent
[~, idx] = sort([subDirs.datenum], 'descend');
latestDir = subDirs(idx(1)).name;
outDir = fullfile(outDirBase, latestDir);

fprintf('Displaying results from: %s\n', outDir);

origPath = fullfile(outDir, 'original.png');
combinedPath = fullfile(outDir, 'combined_overlay.png');

if ~exist(origPath, 'file') || ~exist(combinedPath, 'file')
    error('Required files %s and %s not found in %s', origPath, combinedPath, outDir);
end

I = imread(origPath);
cloudL = imread(fullfile(outDir, 'cloud_labels.png'));
mountainL = imread(fullfile(outDir, 'mountain_labels.png'));

if size(I,3) == 1
    I = repmat(I, [1 1 3]);
end

cloudL = double(cloudL);
mountainL = double(mountainL);

cloud_labels = unique(cloudL(:));
cloud_labels(cloud_labels==0) = []; % remove background/boundary
cloud_n = numel(cloud_labels);

mountain_labels = unique(mountainL(:));
mountain_labels(mountain_labels==0) = []; % remove background/boundary
mountain_n = numel(mountain_labels);

% Generate high-contrast colors consistent with Python HSV scheme
HSV_S = 0.96;
HSV_V = 0.96;

cloud_colors = zeros(cloud_n,3,'uint8');
if cloud_n > 0
    hues = ((0:(cloud_n-1))' / max(cloud_n,1));
    hsv = [hues, HSV_S * ones(cloud_n,1), HSV_V * ones(cloud_n,1)];
    rgb = hsv2rgb(hsv); % double in [0,1]
    cloud_colors = uint8(255 * rgb);
end

mountain_colors = zeros(mountain_n,3,'uint8');
if mountain_n > 0
    hues = 0.5 + ((0:(mountain_n-1))' / max(mountain_n,1));
    hues = mod(hues, 1);
    hsv = [hues, HSV_S * ones(mountain_n,1), HSV_V * ones(mountain_n,1)];
    rgb = hsv2rgb(hsv); % double in [0,1]
    mountain_colors = uint8(255 * rgb);
end

% Build overlay images
alpha = 0.45;
I_double = double(I);

% Function to compute result with given alpha
compute_result = @(a) compute_overlay(a, I_double, cloudL, mountainL, cloud_labels, mountain_labels, cloud_colors, mountain_colors);

result = compute_result(alpha);

% Load intermediate images if they were saved by Python
imgNames = {'cloud_mask.png','mountain_mask.png','cloud_labels.png','mountain_labels.png','cloud_overlay.png','mountain_overlay.png'};
imgs = cell(size(imgNames));
for i = 1:numel(imgNames)
    p = fullfile(outDir, imgNames{i});
    if exist(p,'file')
        imgs{i} = imread(p);
    else
        imgs{i} = [];
    end
end

% Create figure and layout
fig = figure('Name','Watershed Segmentation (intermediates)','NumberTitle','off','Units','normalized','Position',[0.05 0.05 0.9 0.8]);

% Top row: Original and Overlay
ax1 = subplot(3,4,1:2);
imshow(I); title('Original');

ax2 = subplot(3,4,3:4);
hIm = imshow(result); title('Segmentation Overlay');

% Bottom: intermediates in 2nd and 3rd rows (slots 5..12)
positions = 5:12;
for k = 1:numel(imgs)
    ax = subplot(3,4,positions(k));
    if ~isempty(imgs{k})
        imshow(imgs{k});
        title(strrep(imgNames{k},'_',' '),'Interpreter','none');
    else
        axis off; title([strrep(imgNames{k},'_',' ') ' (missing)'],'Interpreter','none');
    end
end

% Controls: alpha slider and save button
uicontrol('Style','text','Units','normalized','Position',[0.38 0.02 0.06 0.03],'String','Alpha','BackgroundColor',get(fig,'Color'));
hSlider = uicontrol('Style','slider','Min',0,'Max',1,'Value',alpha, 'Units','normalized','Position',[0.44 0.02 0.32 0.04], 'Callback',@sliderCallback);
hAlphaText = uicontrol('Style','text','Units','normalized','Position',[0.77 0.02 0.12 0.03],'String',sprintf('Alpha: %.2f',alpha),'BackgroundColor',get(fig,'Color'));
uicontrol('Style','pushbutton','Units','normalized','Position',[0.05 0.02 0.15 0.04],'String','Save Result','Callback',@saveCallback);

outResultPath = fullfile(outDir, 'matlab_overlay.png');

    function sliderCallback(src, ~)
        a = get(src, 'Value');
        newResult = uint8((1 - a) * I_double + a * overlay_double);
        set(hIm, 'CData', newResult);
        set(hAlphaText, 'String', sprintf('Alpha: %.2f', a));
    end

    function saveCallback(~, ~)
        a = get(hSlider, 'Value');
        saveImg = compute_result(a);
        imwrite(saveImg, outResultPath);
        fprintf('Saved MATLAB blended result to %s\n', outResultPath);
    end

end

function result = compute_overlay(a, I_double, cloudL, mountainL, cloud_labels, mountain_labels, cloud_colors, mountain_colors)
    overlay = zeros(size(I_double), 'uint8');
    
    % Cloud overlay
    for k = 1:numel(cloud_labels)
        lbl = cloud_labels(k);
        mask = (cloudL == lbl);
        for c = 1:3
            ch = overlay(:,:,c);
            ch(mask) = cloud_colors(k,c);
            overlay(:,:,c) = ch;
        end
    end
    
    % Mountain overlay
    for k = 1:numel(mountain_labels)
        lbl = mountain_labels(k);
        mask = (mountainL == lbl);
        for c = 1:3
            ch = overlay(:,:,c);
            ch(mask) = mountain_colors(k,c);
            overlay(:,:,c) = ch;
        end
    end
    
    overlay_double = double(overlay);
    result = uint8((1-a) * I_double + a * overlay_double);
end

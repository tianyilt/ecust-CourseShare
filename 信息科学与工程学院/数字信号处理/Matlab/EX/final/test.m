% 读取json文件, 并打印出来
% 读取json文件, 并打印出来

json_file = "D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final\param_setting.json";
json_str = fileread(json_file);
json_obj = jsondecode(json_str);

% 打印该对象的其中一个属性"F0"
size(json_obj.ideal_beat_t)

ideal_beat_t = [1 2 1 2 1];
size(ideal_beat_t)
function [bz,az] = zmapping(bZ,aZ,Nz,Dz)

% Frequency band Transformation from Z-domain to z-domain

% -------------------------------------------------------

% [bz,az] = zmapping(bZ,aZ,Nz,Dz)

% performs:

%          b(z)   b(Z)|

%          ---- = ----|     N(z)

%          a(z)   a(Z)|@Z = ----

%                           D(z)

%

bzord = (length(bZ)-1)*(length(Nz)-1);

azord = (length(aZ)-1)*(length(Dz)-1);



bz = zeros(1,bzord+1);

for k = 0:bzord

    pln = [1];

    for l = 0:k-1

        pln = conv(pln,Nz);

    end

    pld = [1];

    for l = 0:bzord-k-1

        pld = conv(pld,Dz);

    end

    bz = bz+bZ(k+1)*conv(pln,pld);

end



az = zeros(1,azord+1);

for k = 0:azord

    pln = [1];

    for l = 0:k-1

        pln = conv(pln,Nz);

    end

    pld = [1];

    for l = 0:azord-k-1

        pld = conv(pld,Dz);

    end

    az = az+aZ(k+1)*conv(pln,pld);

end



az1 = az(1); az = az/az1; bz = bz/az1;
%author Jing
%function: generate semantic labels
%date: Nov. 8th 2018

img_dir = './SemanticLabels/Mask/';
seg_dir = './SemanticLabels/vessels_64x64_static_3categories/';

names = cell(1,3);
names{1,1} = 'background';
names{1,2} = 'lumen';
names{1,3} = 'plaque';

img_files = dir([img_dir, '*.png']);
for i = 1 : numel(img_files)
    fname = img_files(i).name;
    tmp_name = strsplit(fname, 'MS.png');
    sf = strcat(tmp_name{1,1}, 'C.mat');
    if ~exist( fullfile(seg_dir, sf) )
        img = imread(fullfile(img_dir, fname));
        
        S = uint16(img(:,:,1));
        
        %bg_indx = find( S == 0 );
        lumen_indx = find( S == 128 );
        plaque_indx = find( S == 255 );
        if ~isempty(lumen_indx)
            S( lumen_indx ) = 1;
        end
        if ~isempty(plaque_indx)
            S( plaque_indx ) = 2;
        end
        
        save( fullfile(seg_dir, sf) , 'S', 'names' );
    end
end

%author Jing
%function: from semantic label to geo labels
%date: Nov. 9th 2018
clear;

img_dir = './SemanticLabels/vessels_64x64_static_3categories/';
seg_dir = './GeoLabels/vessels_64x64_static_3categories/';

load( './Meta/vessel_stats.mat' ); % vessel_counts, vessel_names
% metaData = 
count = 0;
names = { 'outlier', 'D1','D2','L-PDA','L-PL','LAD','LCX','OM1','OM2','R-PDA','R-PL','RAMUS','RCA','dLCX' };
% [1795,5857,3457,127,98,22495,15060,6022,2808,4705,3123,3200,16817,68]

count_names = zeros(length(names),1);
img_files = dir([img_dir, '*.mat']);

for i = 1 : numel(img_files)
    fname = img_files(i).name;
    tmp_name = strsplit(fname, '_');
    vesname = tmp_name{1,3};
    load( fullfile( img_dir, fname ) );
    
    S = double( S );
    bg_indx = find( S == 0 );
    lumen_indx = find( S == 1 );
    plaque_indx = find( S == 2 );
    
    switch vesname
       case {'0','KHS','KSH','LHS','RE'}
          color_back = 3;         count_names(1,1) = count_names(1,1) + 1;
        case 'D1'
          color_back = 4;         count_names(2,1) = count_names(2,1) + 1;
        case 'D2'
          color_back = 5;         count_names(3,1) = count_names(3,1) + 1;
        case 'L-PDA'
          color_back = 6;         count_names(4,1) = count_names(4,1) + 1;
        case 'L-PL'
         color_back =  7;         count_names(5,1) = count_names(5,1) + 1;
        case 'LAD'
         color_back =  8;         count_names(6,1) = count_names(6,1) + 1;
        case {'LCX', 'LCX,OM1-CSM'}
            color_back = 9;       count_names(7,1) = count_names(7,1) + 1;
        case 'OM1'
           color_back = 10;        count_names(8,1) = count_names(8,1) + 1;
        case {'OM2', 'OM2-CSM', 'OM2.1'}
           color_back =  11;       count_names(9,1) = count_names(9,1) + 1;
        case 'R-PDA'
            color_back = 12;          count_names(10,1) = count_names(10,1) + 1;
        case 'R-PL'
            color_back = 13;          count_names(11,1) = count_names(11,1) + 1;
        case 'RAMUS'
            color_back = 14;          count_names(12) = count_names(12,1) + 1;
        case {'RCA', 'RCA2','distalRCA'}
            color_back =  15;             count_names(13,1) = count_names(13,1) + 1;
        case 'dLCX'
            color_back = 16;          count_names(14,1) = count_names(14,1) + 1;
    end
    metaData.color_bg = color_back;
    if ~isempty( plaque_indx )
       metaData.class = 3;
    else
        metaData.class = 2;
    end
    if ~isempty( bg_indx )
        S( bg_indx ) = color_back;
    end 
    
    if ~exist( fullfile(seg_dir, fname) )        
        save( fullfile(seg_dir, fname) , 'S', 'names', 'metaData');
    end

    
end
           
            
    
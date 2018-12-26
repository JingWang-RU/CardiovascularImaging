%author Jing
%function: generate semantic labels; 
%          map grayscale image to 3 values [0,128,255] use the 8 neighbors
%date: Dec 24th Christmas Eve 2018

img_dir = '*/Augmentor/medis_aug/aug_MSK/';
seg_dir = './SemanticLabels/vessels_64x64_static_3categories/';

names = cell(1,3);
names{1,1} = 'background';
names{1,2} = 'lumen';
names{1,3} = 'plaque';

img_files = dir([img_dir, '*.png']);
for i = 1 : numel(img_files)
    fname = img_files(i).name;
    tmp_name = strsplit(fname, '.png');
    sf = strcat(tmp_name{1,1}, '.png', tmp_name{1,2}, '.mat');
%     if exist( fullfile(seg_dir, sf) )
        img = imread(fullfile(img_dir, fname));
%         R = (img(:,:,1) *.299);
%         G = (img(:,:,2) *.587);
%         B = (img(:,:,3) *.114);
        S = uint16(img(:,:,1));%uint16(R+G+B);%
        orgS = S;
        bg_indx = find( S==0 );
        lumen_indx = find( S == 128 );
        plaque_indx = find( S == 255 );
        
        nonzero = find(S ~=0 & S ~= 128 & S ~= 255);
        [I, J] = ind2sub(size(S,1), nonzero);
        val  = S(nonzero);
        v = uint16([0, 128, 255]);
        for j = 1:length(nonzero)
            fprintf("x: %d y: %d \n",I(j), I(j));
            temp= [];
            neighb_1 = orgS(I(j)-1, J(j));
            neighb_2 = orgS(I(j)+1, J(j));
            neighb_3 = orgS(I(j), J(j)-1);
            neighb_4 = orgS(I(j), J(j)+1);
            neighb_5 = orgS(I(j)-1, J(j)-1);
            neighb_6 = orgS(I(j)+1, J(j)+1);
            neighb_7 = orgS(I(j)-1, J(j)+1);
            neighb_8 = orgS(I(j)+1, J(j)-1);
            neighb = [neighb_1, neighb_2, neighb_3, neighb_4,neighb_5, neighb_6, neighb_7, neighb_8];
            tru_neighb = intersect(unique(neighb), v);
            
            if ~isempty( tru_neighb )
                diff = abs(bsxfun(@minus, val(j), uint16(tru_neighb)));  
                [~, index] = min(diff); 
                index_v = tru_neighb(index);
            else
                diff = abs(bsxfun(@minus, val(j), uint16(v)));    
                [~, index] = min(diff);   
                index_v = v(index);
            end
            switch index_v
                case 0
%                     fprintf("0")
                    bg_indx = [bg_indx; nonzero(j)];
                case 128
%                     fprintf("128")
                    lumen_indx = [lumen_indx; nonzero(j)];
                case 255
%                     fprintf("255")
                    plaque_indx = [plaque_indx; nonzero(j)];
            end
        end
       
        if ~isempty(bg_indx)
            S( bg_indx ) = 0;
        end
        if ~isempty(lumen_indx)
            S( lumen_indx ) = 1;
        end
        if ~isempty(plaque_indx)
            S( plaque_indx ) = 2;
        end
        save( fullfile(seg_dir, sf) , 'S', 'names' );
%     end
end

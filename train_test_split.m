% author: Jing 
% function: given two files with Class 1 and 2 split them two train test  
%           find the names in imageList.mat and 
%           generate Meta/splits/ train test with index
% output: split: structure with train and test             
% date: Nov. 8th, 2018
clear;
data_dir = './Meta/';
three_class_file = 'threeClass.mat';
two_class_file = 'twoClass.mat';
image_file = 'imageList';
splits.train = [];
splits.test = [];

load ([ data_dir, image_file]);%
imageList = string( imageList );
imageList = strrep(imageList, 'C.png', 'MS.png');

% three class index backlumenplaque
load( [data_dir, three_class_file] );
num_three = length( backlumenplaque );

train_three = randperm( num_three, floor(0.6*num_three) );
test_three = setdiff( [1:num_three], train_three );

train_name_three = backlumenplaque( train_three );
test_name_three = backlumenplaque( test_three );

[~, splits.train] = intersect( imageList, train_name_three );
[~, splits.test] = intersect( imageList, test_name_three );
%three class index backlumen
load( [data_dir, two_class_file] );
num_two = length ( backlumen );

train_two = randperm( num_two, floor(0.6*num_two) );
test_two = setdiff( [1:num_two], train_two );

train_name_two = backlumen( train_two );
test_name_two = backlumen( test_two );

[~, ind_train] = intersect( imageList, train_name_two );
[~, ind_test] = intersect( imageList, test_name_two );

splits.train = [ splits.train; ind_train ];
splits.test = [ splits.test; ind_test ];

save( [data_dir 'splits.mat'], 'splits' );
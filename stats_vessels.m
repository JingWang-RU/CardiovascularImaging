% author: Jing 
% function: number of vessels in each class
% output: summary      
% date: Nov. 8th, 2018
clear;
data_dir = './Meta/imageList.mat';
load( data_dir ); % imageList

stats_vessel = containers.Map;
outlier = ['0','KHS','KSH','LHS','LCX,OM1-CSM','OM2-CSM',...
                'OM2.1','RCA2','distalRCA','dLCX','RE'];
for i = 1:numel(imageList)
   
    fname = strsplit(imageList{i,1}, '_');
%     if fname{1,3} =='0' %only 316782910/2
%         fprintf( imageList{i,1} + "\n" );
%         %fprintf( fname{1,3} + "\n" );
%     end
    %
  
    if isKey(stats_vessel, fname{1,3})
        stats_vessel( fname{1,3} ) = stats_vessel( fname{1,3} ) + 1;
    else
        stats_vessel( fname{1,3} ) = 1; 
        if fname{1,3}=="RE"%ismember(fname{1,3}, outlier)
            fprintf( imageList{i,1} + "\n" );
        end
    end
    
end
vessel_names = ( stats_vessel.keys );
vessel_counts = cell2mat( stats_vessel.values );
% save( './Meta/vessel_stats.mat', 'vessel_names', 'vessel_counts' );
% author: Jing Wang
% function: summary best result
% time: Feb. 2019 
epochs = [140, 150:10:180, 200, 220, 230, 250, 280];

results = zeros(length(epochs), 9);

for i = 1:length(epochs)
     epoch = epochs(i);
     file_name = ['epoch_' num2str(epoch) '_result_dice.mat'];
     load(file_name);
     r1 = mean(lqq_dice(:,1));  
     r2 = mean(lqq_dice(:,2));
     t2 = lqq_dice(:,2);
     r3 = length(find(t2 > 0))/size(lqq_dice,1);
     r4 = mean(t2(find(t2>0)));
     
     r12 = mean(lqq_gt_dice(:,1));  
     r22 = mean(lqq_gt_dice(:,2));
     t22 = lqq_gt_dice(:,2);
     r32 = length(find(t22 > 0))/size(lqq_gt_dice,1);
     r42 = mean(t22(find(t22>0)));     
     results(i,:) = [r1, r2, r3, r4, r12, r22, r32, r42, size(lqq_dice,1)];
end

results = [results; max(results)];


results_stats = zeros(length(epochs), 3);

for i = 1:length(epochs)
     epoch = epochs(i);
     stat_name = ['epoch_' num2str(epoch) '_pixel_accuracy.mat'];
     load(stat_name);
     
     results_stats(i,:) = [stats.pacc, stats.macc, stats.miu];
end

results_stats = [results_stats; max(results_stats)];

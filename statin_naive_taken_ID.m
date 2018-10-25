% function: find the statin taken and statin naive patients, intersect with dicoms at
% hand
% author: jiw2026@med.cornell.edu
% time: Oct. 24th 2018
[pre_statin_naive,~]=find(AncillaryDataPARADIGM.Pre_Statin==0);
[post_statin_naive,~]=find(AncillaryDataPARADIGM.post_Statin==0);

row_statin_naive = intersect(pre_statin_naive, post_statin_naive);

[post_statin_taken, ~] = find(AncillaryDataPARADIGM.post_Statin==1);

row_statin_taken = post_statin_taken;

id_statin_naive = AncillaryDataPARADIGM(row_statin_naive,:).NewID;
id_statin_taken = AncillaryDataPARADIGM(row_statin_taken,:).NewID;

save('statin_naive_taken_newID.mat', 'pre_statin_naive', ...
    'post_statin_naive', 'row_statin_naive', 'post_statin_taken', 'row_statin_taken','id_statin_naive','id_statin_taken');

id_dicom_naive = intersect(ids, id_statin_naive);
id_dicom_taken = intersect(ids, id_statin_taken);
save('statin_naive_taken_dicom_newID.mat','id_dicom_naive','id_dicom_taken');

% subid_dicom_naive is NULL, becase NewID maps 
load 'statin_naive_taken_newID.mat';
subid_statin_naive = AncillaryDataPARADIGM(row_statin_naive,:).Subject_ID;
subid_statin_taken = AncillaryDataPARADIGM(row_statin_taken,:).Subject_ID;
subid_dicom_naive = intersect(ids, subid_statin_naive);
subid_dicom_taken = intersect(ids, subid_statin_taken);
save('statin_naive_taken_dicom_subID.mat','subid_dicom_naive','subid_dicom_taken');

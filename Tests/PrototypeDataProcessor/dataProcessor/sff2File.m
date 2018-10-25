function sff2File(filename, title, labels, separator, vs, vf1, vf2)
% sff2File - save data on csv format on file
%
% Syntax: sff2File(filename, title, labels, separator, vs, vf1, vf2)
%
% Inputs:
%    filename -
%    title  -
%    labels  -
%    separator  -
%    vs  -
%    vf1 -
%    vf2  -
%
% Outputs:
%    fig - figure object
%
% Example: 
%    sff2File(filename, title, labels, separator, vs, vf1, vf2)
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% Author: Anderson Paschoalon
% email: anderson.paschoalon@gmail.com
% Sep 2018: Last revision: 16-Sep-2018  
	fid = fopen(filename,'wt');
	fprintf(fid, "#%s\n", title);
	fprintf(fid, "#%s\n", labels);
	vf1 = reshape(vf1, [], 1);
	vf1 = reshape(vf1, [], 1);
	m = size(vs, 1);
	for i = 1:m
		fprintf(fid, "%s%c%f%c%f\n", vs(i, :), separator, vf1(i), separator, vf2(i));
	endfor
	%dlmwrite(fid, M, "-append");
	fclose(fid);
end
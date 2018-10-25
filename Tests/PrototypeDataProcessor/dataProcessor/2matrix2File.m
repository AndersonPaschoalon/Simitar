% used?
function matrix2File(M, filename, title, labels)
% matrix2File - save a matrx to a file. It also adds two comment lines 
% (starting with #). The first is the title of the file, the second is the 
% list of labels for each column
%
% Syntax:  matrix2File(M, filename, title, labels)
%
% Inputs:
%    M - matrix to be saved in a text file 
%    filename - name of the destination text file 
%    title - title of the matrix 
%    labels - labels of each column from the matrix 
%
% Outputs:
%    none
%
% Example: 
%    M = [1 2 3; 4 5 6]
%    matrix2File(M, 'numbers', 'Numbers', 'v1, v2, v3')
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
	dlmwrite(fid, M, "-append");
	fclose(fid)
end
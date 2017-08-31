function matrix2File(M, filename, title, labels)
	fid = fopen(filename,'wt');
	fprintf(fid, "#%s\n", title);
	fprintf(fid, "#%s\n", labels);
	dlmwrite(fid, M, "-append");
	fclose(fid)
end
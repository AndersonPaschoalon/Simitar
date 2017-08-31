function matrix2File(M, filename, title, labels)
	fprintf(filename)
	fid = fopen(filename,'wt');
	fprintf(fid, "#%s\n", title);
	fprintf(fid, "#%s\n", labels);
	dlmwrite(fid, real(M), "-append");
	fclose(fid);
end

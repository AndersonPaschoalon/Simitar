function emCdf = empiricalCdf2(data)
        %convert to C++
        data_size = length(data);
        x = data(1);
        i1 = 1;%first index 
        i2 = 1;
        emCdf = zeros(data_size, 1);
        for i = 1:data_size
                if(data(i) > x)
                        i2 = i - 1;
                        p = (i - 1)/data_size;
                        for j = i1:i2
                                emCdf(j) = p; 
                        endfor
                        i1 = i;
                        x = data(i);
                endif
        endfor
        emCdf(data_size) = 1;
end
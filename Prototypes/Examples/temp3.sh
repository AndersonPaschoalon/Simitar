awk '
    FNR == 1 {

        ## Process first line.
        print FNR ": " $0;

        while ( getline == 1 ) {
            ## Process from second to last line.
            print FNR ": " $0;
        }

        ## Here all lines have been processed.
        print "After last line";
    }
' temp2.sh




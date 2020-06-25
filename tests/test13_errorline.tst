start
    int[] arr = [1,2,3,4,5];
    arr.forEach(x->{
        arr.forEach(x->{
            if (x > 1){
                print "A" ;
            } else {
                print "B" ;
            }
        }
        );
        if (x > 3){
            print "C" ;
        } else {
            print "D" ;
        }
    });
    arr.forEach(x->{
        if (x > 3){
            print "E" ;
        } else {
            print "F" ;
        }
    });
    arr.forEach(y->{
        if (y > 1){
            print "G" ;
        } else {
            print "H" ;
        }
    });
end
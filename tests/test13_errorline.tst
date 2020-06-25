start
    int[] arr = [1,2,3,4,5];
    arr.forEach(x->{
        arr.forEach(y->{
        if (y > 1){
            print "JEJE" ;
        } else {
            print "JAJA" ;
        }
    }
        );
        if (x > 3){
            print "Hola" ;
        } else {
            print "Chau" ;
        }
    });
    arr.forEach(x->{
        if (x > 3){
            print "Chau" ;
        } else {
            print "Hola" ;
        }
    });
    arr.forEach(y->{
        if (y > 1){
            print "JEJE" ;
        } else {
            print "JAJA" ;
        }
    });
end
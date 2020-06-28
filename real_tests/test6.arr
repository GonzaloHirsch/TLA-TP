start
    print "This program evaluates the cross and escalar product of two vectors";
    double[] arr1 = [0.0,0,0];
    double[] arr2 = [0.0,0,0];
    double[] resArrDoub;
    double resDoub;
    int size;

    print "First Choose the size of the vectors ( 2 o 3):";
    size = getInt();

    if(size != 2 && size != 3){
        print "ERROR SIZE MUST BE 2 o 3";
    }

    print "Choose the values for the first arrays";
    int i =0;
    while(i < size){
       arr1[i] = getDouble();
       i=i+1;
    }

    print "Choose the values for the second arrays";
    i =0;
    while(i < size){
        arr2[i] = getDouble();
        i = i +1;
    }

    print "CROSS PRODUCT: ";
    resArrDoub = arr1 cross arr2;
    print resArrDoub;

    print "SCALAR PRODUCT: ";
    resDoub = arr1 *. arr2;
    print resDoub;

    print "GOODBYE";
    
end

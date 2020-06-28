start
    print "This program evaluates operations of two arrays of size 5";
    double[] arr1 = [0.0,0,0,0,0];
    double[] arr2 = [0.0,0,0,0,0];
    double[] res;

    print "Choose the values for the first arrays";
    int i =0;
    while(i < 5){
       arr1[i] = getDouble();
       i=i+1;
    }

    print "Choose the values for the second arrays";
    i =0;
    while(i < 5){
        arr2[i] = getDouble();
        i = i +1;
    }

    print "Choose the operation: 1. * 2. + 3. / 4. -";
    int op = getInt();

    if(op == 1){
        res = arr1 * arr2;
    }
    else if(op == 2){
        res = arr1 + arr2;
    }
    else if(op == 3){
        res = arr1 / arr2;
    }
    else if(op == 4){
        res = arr1 - arr2;
    }
    else {
        print "Invalid Choice";
        exit();
    }

    print "Result";
    print res;
    
end
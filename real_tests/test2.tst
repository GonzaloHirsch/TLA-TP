start
    double[] arr1 = [1.0, 2, 3, 4, 5];
    double[] arr2 = [1.0, 2 ,3 ,4 , 5];
    double[] arr3 = [1.0, 2 ,3 ,4 , 5,6];

    double[] arr4 = arr2/arr1;


    double[] res = arr1/arr2;
    res.forEach(x->{
        print x;
        if(x != 1){
            print "x is not 1";
        }
    });

end
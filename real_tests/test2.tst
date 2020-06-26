start
    double[] arr1 = [1.0, 2, 3, 4, 5];
    double[] arr2 = [1.0, 2 ,3 ,4 , 5];

    double[] res = arr1/arr2;
    res.forEach(x->{
        print x;
        if(x != 1){
            print "x is not 1";
        }
    });

    double[] arr3 = [1.0,2,3];
    int[] arr4 = [1,1,1];

    double[] arr5 = arr3 cross arr4;
    print arr5;

end
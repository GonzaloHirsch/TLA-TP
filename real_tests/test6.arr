start 
    print "This program tests many operations";

    double[] arr1 = [1.1,2,3,4.4,5];
    double[] arr2 = [2.0, 7, 3];
    double[] arr3 = [1, 7.0, 3];
    int[] arr4 = [1, 2, 3];
    int[] arr5 = [1, 2, 3, 4, 5];

    double[] res1;
    int[] res2;
    double res3;
    int res4;

    print "CROSS";

    res1 = arr3 cross arr4;
    print res1;

    res1 = arr4 cross arr3;
    print res1;

    res1 = arr2 cross arr3;
    print res1;

    res1 = arr3 cross arr2;
    print res1;

    print "SCALAR";

    res3= arr3 *. arr4;
    print res3;

    res3 = arr4 *. arr3;
    print res3;

    res3 = arr2 *. arr3;
    print res3;

    res3 = arr3 *. arr2;
    print res3;
  
end
start
    print "This program evaluates operations between an array integer(Size 5) and integers\n";
    int[] arr1 = [0,0,0,0,0];
    int[] integers = [0,0,0];
    int[] resArr;
    double[] resArrD;
 
    int size = 5;

    print "Choose the values for the array\n";
    int i =0;
    while(i < size){
       arr1[i] = getInt();
       i=i+1;
    }

    print "Choose the values for the integers (3)\n";
    i =0;
    while(i < 3){
        integers[i] = getInt();
        i = i +1;
    }

    print "--------------------\n You array is: \n";
    print arr1;
    print "--------------------\n";
    integers.forEach(x ->{
        print "Add "; print x; print"\n";
        resArr = arr1 + x;
        print resArr;

        print "Sub "; print x; print"\n";
        resArr = arr1 - x;
        print resArr;

        print "Prod "; print x; print"\n";
        resArr = arr1 * x;
        print resArr;

        print "Div "; print x; print"\n";
        resArrD = arr1 / x;
        print resArrD;
        
        print "-------------------\n";

    });
    
end
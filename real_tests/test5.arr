start 
    print "This program asks a user for input and concatenates strings";
    print "First string to concat";
    str first = getString();
    print "Second string to concat";
    str second = getString();
    print "Third string to concat";
    str third = getString();
    str res = first + second + third;
    print res;

    int[] arr = [1, 1, 1];
    int f = 0;
    arr.forEach(x->{
        f = f + x;
        print f;
    });

    f = f + 20;
    print f;
end
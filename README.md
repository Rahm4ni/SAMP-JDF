# SAMP-JDF
an include that can help you to convert gregorian to jalali or jalali to gregorian.

# Example Usage
```
    new jy, jm, jd;
    alali(2016, 10, 7, jy, jm, jd);
    printf("%d/%d/%d", jy, jm, jd); //Will return: 1395/7/16
    __________________________________________________________
    new gy, gm, gd;
    gregorian(1395, 7, 16, gy, gm, gd);
    printf("%d/%d/%d", gy, gm, gd); //Will return: 2016/10/7
    __________________________________________________________
    new y, m, d;
    jdate(y, m, d);
    printf("%d/%d/%d", y, m, d); //Will return current Jalali date
    __________________________________________________________
    print(jtimestamp()); //Will return current Jalali time stamp
```

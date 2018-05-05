xx = 0:100;
yy = sqrt(100^2 - xx.^2);
dd = - atand(xx./yy);
dd = 0:100
dd = dd*-90/100
plot(xx,yy)
axis equal

vv = 2*314.159265 * ones(1, 101) / 404;

matrix.glider(:,6) = vv;
matrix.glider(:,9) = dd;
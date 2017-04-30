function [details EnergyDet] = haar_1d ( n, u )

%*****************************************************************************80
%
%% HAAR_1D computes the Haar transform of a vector, and the resolution energy.
%
%  Discussion:
%
%    Modified version of the function, with comentaties. The original can be 
%    found at https://people.sc.fsu.edu/~jburkardt/m_src/haar/haar_1d.m 
%
%  Licensing:
%
%    This code is distributed under the GNU LGPL license.
%
%  Modified:
%
%    05 March 2014
%
%  Author:
%
%    John Burkardt
%
%  Parameters:
%
%    Input, integer N, the length of the vector.
%
%    Input, real U(N,1), the vector to be transformed.
%
%    Output, real V(N,1), the transformed vector.
%
v = u(:);

s = sqrt ( 2.0 );

w = zeros ( n, 1 );
  
%
%  Determine K, the largest power of 2 such that K <= N.
%
k = 1;
while ( k * 2 <= n )
        k = k * 2;
end

%number of time-scales
J = log2(k);
  
%details energy
Ed = zeros(J, 1);
%energy index 
iE = 1;
%last detail to be picket at the current interation
dEnd = k;
  
  
while ( 1 < k )
  
        k = floor ( k / 2 );
    
        %new coarsen time serie computation
        w(  1:  k) = ( v(1:2:2*k-1) + v(2:2:2*k) ) / s;
        %detail computation
        w(k+1:k+k) = ( v(1:2:2*k-1) - v(2:2:2*k) ) / s;
        %detail storing 
        v(1:2*k) = w(1:2*k);

        %pick the details evaluated at the current iteration
        d = v((k+1):dEnd);
   
        %energy evaluation 
        Ed(iE) = 1/(length(d))*sum(d.^2);
    
        %update energy vector position and last detail to be picked
        %in the next iteration
        iE = iE + 1;
        dEnd = k;
    
end

details = v;
EnergyDet = Ed;

return
end

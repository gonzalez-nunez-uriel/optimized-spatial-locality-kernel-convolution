This function applies a convolution kernel, provided that the kernel has an odd
size (not necessarily a square). It implements an optimization: it uses the
spatial locality of a 1-dimensional array to apply the kernel. In theory, this
should reduce the number of cache misses when applying the kernel.

In practice, this optimization cannot be used. Most libraries read images as
a 2-dimensional array implemented using 2 1-dimensional arrays, one with data
and another with pointers to the data. For modern systems with large caches,
the optimization I made does not lead to a significant improvement. The effort
needed to change these 2-dim arrays into a 1-dim array outweigh any benefit from
this implementation. Regardless, it was a good exercise.

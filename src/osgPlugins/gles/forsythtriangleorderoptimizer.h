﻿//-----------------------------------------------------------------------------
//  This is an implementation of Tom Forsyth's "Linear-Speed Vertex Cache
//  Optimization" algorithm as described here:
//  http://home.comcast.net/~tom_forsyth/papers/fast_vert_cache_opt.html
//
//  This code was authored and released into the public domain by
//  Adrian Stone (stone@gameangst.com).
//
//  THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
//  SHALL ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER
//  LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
//  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef __FORSYTH_TRIANGLE_REORDER__
#define __FORSYTH_TRIANGLE_REORDER__

namespace Forsyth
{
    //-----------------------------------------------------------------------------
    //  OptimizeFaces
    //-----------------------------------------------------------------------------
    //  Parameters:
    //      indexList
    //          input index list
    //      indexCount
    //          the number of indices in the list
    //      vertexCount
    //          the largest index value in indexList
    //      newIndexList
    //          a pointer to a preallocated buffer the same size as indexList to
    //          hold the optimized index list
    //      lruCacheSize
    //          the size of the simulated post-transform cache (max:64)
    //-----------------------------------------------------------------------------
    void OptimizeFaces(const unsigned int* indexList,
                       unsigned int indexCount,
                       unsigned int vertexCount,
                       unsigned int* newIndexList,
                       unsigned int lruCacheSize);

} // namespace Forsyth

#endif // __FORSYTH_TRIANGLE_REORDER__

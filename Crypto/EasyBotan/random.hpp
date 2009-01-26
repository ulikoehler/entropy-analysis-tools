/* 
 * File:   random.hpp
 * Author: uli
 *
 * Created on 19. Januar 2009, 16:10
 */

#ifndef _RANDOM_HPP
#define	_RANDOM_HPP

/**
 * Generates a file containing random data ("entropy")
 * @param outfile The filename to write the entropy to
 * @param size The number of bytes to write out
 */
void generateEntropyFile(string outfile, ulong size);

#endif	/* _RANDOM_HPP */


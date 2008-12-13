/* 
 * File:   output.hpp
 * Author: uli
 *
 * Created on 12. Dezember 2008, 19:03
 */

#ifndef _OUTPUT_HPP
#define	_OUTPUT_HPP

inline void
print2ColumnOccurrenceStatistics (ostream& of)
{
    BOOST_FOREACH (p, allOcc)
    {
        of << p.first << separator << format(ldFormatString) % p.second << "\n";
    }
}

#endif	/* _OUTPUT_HPP */


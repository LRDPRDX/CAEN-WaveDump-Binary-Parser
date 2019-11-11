#ifndef CAEN_AUXILIARY_H
#define CAEN_AUXILIARY_H

#include <iostream>
#include <iomanip>


namespace caen
{
    //Printing function
    template< typename T >
    inline void PrintParam( const std::string& param_description,
                            T param_value,
                            unsigned description_fill_length )
    {
        std::cout << std::setw( description_fill_length) << param_description << " : " << param_value << "\n";
    }


    inline void PrintHeader( const std::string& header,
                             unsigned length )
    {
        if( length < header.length() ) { length = header.length(); }
        unsigned left = (length - header.length())/2 + header.length();
        unsigned right = (length - left);
        std::cout << std::setfill('=') << std::setw(left) << header << std::setw(right) << "\n";
        std::cout << std::setfill(' ');
    }


    inline void PrintHRule( unsigned length )
    {
        std::cout << std::setfill('=') << std::setw( length ) << "\n";
        std::cout << std::setfill(' ');
    }


    inline void PrintWarning( const std::string& message )
    {
        std::cout << "WARNING :: " << message << std::endl;
    }


    inline void PrintInfo( const std::string& message )
    {
        std::cout << "INFO :: " << message << std::endl;
    }
}

#endif

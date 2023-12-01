/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 00:25:27 by dmartiro          #+#    #+#             */
/*   Updated: 2023/12/02 00:37:21 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP
#include "Libs.hpp"

class Parser
{
    public:
        Parser(std::string const &confFile);
        ~Parser();
    private:
        void start( void );
    private:
        std::fstream IO;
};

#endif
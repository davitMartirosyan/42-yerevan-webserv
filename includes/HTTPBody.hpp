/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPBody.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 02:18:28 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/21 02:23:14 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_BODY_HPP
#define HTTP_BODY_HPP
#include "Libs.hpp"

struct HTTPBody
{
    std::string contentDisposition;
    std::string inputName;
    std::string fileContentType;
    
};

#endif
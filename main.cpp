/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m3ayz00 <m3ayz00@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:19:41 by msaadidi          #+#    #+#             */
/*   Updated: 2024/10/26 15:15:45 by m3ayz00          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NetworkScanner.hpp"

int main()
{
    NetworkScanner NS("192.168.0.0", "192.168.0.0");
    NS.scanNetwork();
    NS.outputResults();
}
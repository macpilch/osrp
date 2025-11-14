/*----------------------------------------------------------------------------*-
					========================================
					 y_stringhash - Fast string comparisons 
					========================================
Description:
	Allows you to hash strings at compile time to use them in a switch.
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the SA:MP script information include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2008
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk
	
	Thanks:
		Peter, Cam - Support.
		ZeeX - Very productive conversations.
		koolk - IsPlayerinAreaEx code.
		TheAlpha - Danish translation.
		breadfish - German translation.
		Fireburn - Dutch translation.
		yom - French translation.
		50p - Polish translation.
		Zamaroht - Spanish translation.
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN.
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
Version:
	1.6
Changelog:
	06/03/11:
		Changed the order of some letters to better support numbers in _I.
	01/03/11:
		Rewrote compile-time hashes to not require commas.
	25/10/10:
		Updated comments.
		Added to YSI 1.0.
		Added FNV1 and FNV1a hashes to avoid collisions.
	19/08/10:
		First version.
Functions:
	stock:
		YHash - Generate a string hash at run time.
Definitions:
	_H - Generate a string hash at compile time.
	_I - Generate a case insensitive string hash at compile time.
-*----------------------------------------------------------------------------*/

#include <YSI\internal\y_version>

// ===================
//  Determine version 
// ===================

// Entry.
#define _H (_:_H_0:_H_1
#define _I (_:_H_2:_H_3
// Old.
#define _H_0:_H_1(%0) HASH@bernstein(%0))
#define _H_2:_H_3(%0) HASHi@bernstein(%0))
// New.
#define _H_1<%0> _:H_Rb(%0)) //HASh@bernstein(%0)
#define _H_3<%0> _:H_Rc(%0))

// Entry.
#define _H@b (_:_H0@b:_H1@b
#define _I@b (_:_H2@b:_H3@b
// Old.
#define _H0@b:_H1@b(%0) HASH@bernstein(%0))
#define _H2@b:_H3@b(%0) HASHi@bernstein(%0))
// New.
#define _H1@b<%0> _:H_Rb(%0))
#define _H3@b<%0> _:H_Rc(%0))

// Entry.
#define _H@f (_:_H0@f:_H1@f
#define _I@f (_:_H2@f:_H3@f
// Old.
#define _H0@f:_H1@f(%0) HASH@fnv1(%0))
#define _H2@f:_H3@f(%0) HASHi@fnv1(%0))
// New.
#define _H1@f<%0> _:H_Rg(%0))
#define _H3@f<%0> _:H_Rf(%0))

// Entry.
#define _H@a (_:_H0@a:_H1@a
#define _I@a (_:_H2@a:_H3@a
// Old.
#define _H0@a:_H1@a(%0) HASH@fnv1a(%0))
#define _H2@a:_H3@a(%0) HASHi@fnv1a(%0))
// New.
#define _H1@a<%0> _:H_Ra(%0))
#define _H3@a<%0> _:H_Rd(%0))

// Entry.
#define HASH  (_:_H_4:_H_5
#define HASHi (_:_H_6:_H_7
// Old.
#define _H_4:_H_5(%0,%1) HASH@%0(%1))
#define _H_6:_H_7(%0,%1) HASHi@%0(%1))
// New.
#define _H_5:%0<%1> HASh@%0(%1))
#define _H_7:%0<%1> HAShi@%0(%1))

#define HASh@bernstein(%0) (_:H_Rb(%0))
#define HAShi@bernstein(%0) (_:H_Rc(%0))
#define HASh@fnv1(%0) (_:H_Rg(%0))
#define HAShi@fnv1(%0) (_:H_Rg(%0))
#define HASh@fnv1a(%0) (_:H_Ra(%0))
#define HAShi@fnv1a(%0) (_:H_Rd(%0))

// =============
//  New version 
// =============

// ================
//  Bernstein hash 
// ================

// ================
//  Case sensitive 
// ================

// Do the next character test as this one failed.
#define H_Sb(%0,%1) H_Nb%1(%0)
// End of string test failed.
#define H_Eb(%0)    hba:H_Sb(%0,a)
// Do the single addition.
#define H_Db(%0,%1) (_:H_Rb(%0)*33+%1)
// Recurse through the string.
#define H_Rb(%0)    hb:H_Eb(%0)
// Test for the end of a string.
#define hb:H_Eb()   -1
// Find the length of a string at compile time.
//#define LEN(%0) _:(H_R(%0))

// Test for the current character.
#define hba:H_Sb(a%0,%1) H_Db(%0,97)
#define hbb:H_Sb(b%0,%1) H_Db(%0,98)
#define hbc:H_Sb(c%0,%1) H_Db(%0,99)
#define hbd:H_Sb(d%0,%1) H_Db(%0,100)
#define hbe:H_Sb(e%0,%1) H_Db(%0,101)
#define hbf:H_Sb(f%0,%1) H_Db(%0,102)
#define hbg:H_Sb(g%0,%1) H_Db(%0,103)
#define hbh:H_Sb(h%0,%1) H_Db(%0,104)
#define hbi:H_Sb(i%0,%1) H_Db(%0,105)
#define hbj:H_Sb(j%0,%1) H_Db(%0,106)
#define hbk:H_Sb(k%0,%1) H_Db(%0,107)
#define hbl:H_Sb(l%0,%1) H_Db(%0,108)
#define hbm:H_Sb(m%0,%1) H_Db(%0,109)
#define hbn:H_Sb(n%0,%1) H_Db(%0,110)
#define hbo:H_Sb(o%0,%1) H_Db(%0,111)
#define hbp:H_Sb(p%0,%1) H_Db(%0,112)
#define hbq:H_Sb(q%0,%1) H_Db(%0,113)
#define hbr:H_Sb(r%0,%1) H_Db(%0,114)
#define hbs:H_Sb(s%0,%1) H_Db(%0,115)
#define hbt:H_Sb(t%0,%1) H_Db(%0,116)
#define hbu:H_Sb(u%0,%1) H_Db(%0,117)
#define hbv:H_Sb(v%0,%1) H_Db(%0,118)
#define hbw:H_Sb(w%0,%1) H_Db(%0,119)
#define hbx:H_Sb(x%0,%1) H_Db(%0,120)
#define hby:H_Sb(y%0,%1) H_Db(%0,121)
#define hbz:H_Sb(z%0,%1) H_Db(%0,122)

#define hbA:H_Sb(A%0,%1) H_Db(%0,65)
#define hbB:H_Sb(B%0,%1) H_Db(%0,66)
#define hbC:H_Sb(C%0,%1) H_Db(%0,67)
#define hbD:H_Sb(D%0,%1) H_Db(%0,68)
#define hbE:H_Sb(E%0,%1) H_Db(%0,69)
#define hbF:H_Sb(F%0,%1) H_Db(%0,70)
#define hbG:H_Sb(G%0,%1) H_Db(%0,71)
#define hbH:H_Sb(H%0,%1) H_Db(%0,72)
#define hbI:H_Sb(I%0,%1) H_Db(%0,73)
#define hbJ:H_Sb(J%0,%1) H_Db(%0,74)
#define hbK:H_Sb(K%0,%1) H_Db(%0,75)
#define hbL:H_Sb(L%0,%1) H_Db(%0,76)
#define hbM:H_Sb(M%0,%1) H_Db(%0,77)
#define hbN:H_Sb(N%0,%1) H_Db(%0,78)
#define hbO:H_Sb(O%0,%1) H_Db(%0,79)
#define hbP:H_Sb(P%0,%1) H_Db(%0,80)
#define hbQ:H_Sb(Q%0,%1) H_Db(%0,81)
#define hbR:H_Sb(R%0,%1) H_Db(%0,82)
#define hbS:H_Sb(S%0,%1) H_Db(%0,83)
#define hbT:H_Sb(T%0,%1) H_Db(%0,84)
#define hbU:H_Sb(U%0,%1) H_Db(%0,85)
#define hbV:H_Sb(V%0,%1) H_Db(%0,86)
#define hbW:H_Sb(W%0,%1) H_Db(%0,87)
#define hbX:H_Sb(X%0,%1) H_Db(%0,88)
#define hbY:H_Sb(Y%0,%1) H_Db(%0,89)
#define hbZ:H_Sb(Z%0,%1) H_Db(%0,90)

#define hb0:H_Sb(0%0,%1) H_Db(%0,48)
#define hb1:H_Sb(1%0,%1) H_Db(%0,49)
#define hb2:H_Sb(2%0,%1) H_Db(%0,50)
#define hb3:H_Sb(3%0,%1) H_Db(%0,51)
#define hb4:H_Sb(4%0,%1) H_Db(%0,52)
#define hb5:H_Sb(5%0,%1) H_Db(%0,53)
#define hb6:H_Sb(6%0,%1) H_Db(%0,54)
#define hb7:H_Sb(7%0,%1) H_Db(%0,55)
#define hb8:H_Sb(8%0,%1) H_Db(%0,56)
#define hb9:H_Sb(9%0,%1) H_Db(%0,57)

#define hb_:H_Sb(_%0,%1) H_Db(%0,95)
//#define hb@:H_Sb(@%0,%1) H_Db(%0)

// Find the next character to test.
#define H_Nba(%0) hbb:H_Sb(%0,b)
#define H_Nbb(%0) hbc:H_Sb(%0,c)
#define H_Nbc(%0) hbd:H_Sb(%0,d)
#define H_Nbd(%0) hbe:H_Sb(%0,e)
#define H_Nbe(%0) hbf:H_Sb(%0,f)
#define H_Nbf(%0) hbg:H_Sb(%0,g)
#define H_Nbg(%0) hbh:H_Sb(%0,h)
#define H_Nbh(%0) hbi:H_Sb(%0,i)
#define H_Nbi(%0) hbj:H_Sb(%0,j)
#define H_Nbj(%0) hbk:H_Sb(%0,k)
#define H_Nbk(%0) hbl:H_Sb(%0,l)
#define H_Nbl(%0) hbm:H_Sb(%0,m)
#define H_Nbm(%0) hbn:H_Sb(%0,n)
#define H_Nbn(%0) hbo:H_Sb(%0,o)
#define H_Nbo(%0) hbp:H_Sb(%0,p)
#define H_Nbp(%0) hbq:H_Sb(%0,q)
#define H_Nbq(%0) hbr:H_Sb(%0,r)
#define H_Nbr(%0) hbs:H_Sb(%0,s)
#define H_Nbs(%0) hbt:H_Sb(%0,t)
#define H_Nbt(%0) hbu:H_Sb(%0,u)
#define H_Nbu(%0) hbv:H_Sb(%0,v)
#define H_Nbv(%0) hbw:H_Sb(%0,w)
#define H_Nbw(%0) hbx:H_Sb(%0,x)
#define H_Nbx(%0) hby:H_Sb(%0,y)
#define H_Nby(%0) hbz:H_Sb(%0,z)
#define H_Nbz(%0) hbA:H_Sb(%0,0)

#define H_NbA(%0) hbB:H_Sb(%0,B)
#define H_NbB(%0) hbC:H_Sb(%0,C)
#define H_NbC(%0) hbD:H_Sb(%0,D)
#define H_NbD(%0) hbE:H_Sb(%0,E)
#define H_NbE(%0) hbF:H_Sb(%0,F)
#define H_NbF(%0) hbG:H_Sb(%0,G)
#define H_NbG(%0) hbH:H_Sb(%0,H)
#define H_NbH(%0) hbI:H_Sb(%0,I)
#define H_NbI(%0) hbJ:H_Sb(%0,J)
#define H_NbJ(%0) hbK:H_Sb(%0,K)
#define H_NbK(%0) hbL:H_Sb(%0,L)
#define H_NbL(%0) hbM:H_Sb(%0,M)
#define H_NbM(%0) hbN:H_Sb(%0,N)
#define H_NbN(%0) hbO:H_Sb(%0,O)
#define H_NbO(%0) hbP:H_Sb(%0,P)
#define H_NbP(%0) hbQ:H_Sb(%0,Q)
#define H_NbQ(%0) hbR:H_Sb(%0,R)
#define H_NbR(%0) hbS:H_Sb(%0,S)
#define H_NbS(%0) hbT:H_Sb(%0,T)
#define H_NbT(%0) hbU:H_Sb(%0,U)
#define H_NbU(%0) hbV:H_Sb(%0,V)
#define H_NbV(%0) hbW:H_Sb(%0,W)
#define H_NbW(%0) hbX:H_Sb(%0,X)
#define H_NbX(%0) hbY:H_Sb(%0,Y)
#define H_NbY(%0) hbZ:H_Sb(%0,Z)
#define H_NbZ(%0) -1

#define H_Nb0(%0) hb1:H_Sb(%0,1)
#define H_Nb1(%0) hb2:H_Sb(%0,2)
#define H_Nb2(%0) hb3:H_Sb(%0,3)
#define H_Nb3(%0) hb4:H_Sb(%0,4)
#define H_Nb4(%0) hb5:H_Sb(%0,5)
#define H_Nb5(%0) hb6:H_Sb(%0,6)
#define H_Nb6(%0) hb7:H_Sb(%0,7)
#define H_Nb7(%0) hb8:H_Sb(%0,8)
#define H_Nb8(%0) hb9:H_Sb(%0,9)
#define H_Nb9(%0) hb_:H_Sb(%0,_)

#define H_Nb_(%0) hb_:H_Sb(%0,A)

// ==================
//  Case insensitive 
// ==================

// Do the next character test as this one failed.
#define H_Sc(%0,%1) H_Nc%1(%0)
// End of string test failed.
#define H_Ec(%0)    hca:H_Sc(%0,a)
// Do the single addition.
#define H_Dc(%0,%1) (_:H_Rc(%0)*33+%1)
// Recurse through the string.
#define H_Rc(%0)    hc:H_Ec(%0)
// Test for the end of a string.
#define hc:H_Ec()   -1
// Find the length of a string at compile time.
//#define LEN(%0) _:(I_R(%0))

// Test for the current character.
#define hca:H_Sc(a%0,%1) H_Dc(%0,65)
#define hcb:H_Sc(b%0,%1) H_Dc(%0,66)
#define hcc:H_Sc(c%0,%1) H_Dc(%0,67)
#define hcd:H_Sc(d%0,%1) H_Dc(%0,68)
#define hce:H_Sc(e%0,%1) H_Dc(%0,69)
#define hcf:H_Sc(f%0,%1) H_Dc(%0,70)
#define hcg:H_Sc(g%0,%1) H_Dc(%0,71)
#define hch:H_Sc(h%0,%1) H_Dc(%0,72)
#define hci:H_Sc(i%0,%1) H_Dc(%0,73)
#define hcj:H_Sc(j%0,%1) H_Dc(%0,74)
#define hck:H_Sc(k%0,%1) H_Dc(%0,75)
#define hcl:H_Sc(l%0,%1) H_Dc(%0,76)
#define hcm:H_Sc(m%0,%1) H_Dc(%0,77)
#define hcn:H_Sc(n%0,%1) H_Dc(%0,78)
#define hco:H_Sc(o%0,%1) H_Dc(%0,79)
#define hcp:H_Sc(p%0,%1) H_Dc(%0,80)
#define hcq:H_Sc(q%0,%1) H_Dc(%0,81)
#define hcr:H_Sc(r%0,%1) H_Dc(%0,82)
#define hcs:H_Sc(s%0,%1) H_Dc(%0,83)
#define hct:H_Sc(t%0,%1) H_Dc(%0,84)
#define hcu:H_Sc(u%0,%1) H_Dc(%0,85)
#define hcv:H_Sc(v%0,%1) H_Dc(%0,86)
#define hcw:H_Sc(w%0,%1) H_Dc(%0,87)
#define hcx:H_Sc(x%0,%1) H_Dc(%0,88)
#define hcy:H_Sc(y%0,%1) H_Dc(%0,89)
#define hcz:H_Sc(z%0,%1) H_Dc(%0,90)

#define hcA:H_Sc(A%0,%1) H_Dc(%0,65)
#define hcB:H_Sc(B%0,%1) H_Dc(%0,66)
#define hcC:H_Sc(C%0,%1) H_Dc(%0,67)
#define hcD:H_Sc(D%0,%1) H_Dc(%0,68)
#define hcE:H_Sc(E%0,%1) H_Dc(%0,69)
#define hcF:H_Sc(F%0,%1) H_Dc(%0,70)
#define hcG:H_Sc(G%0,%1) H_Dc(%0,71)
#define hcH:H_Sc(H%0,%1) H_Dc(%0,72)
#define hcI:H_Sc(I%0,%1) H_Dc(%0,73)
#define hcJ:H_Sc(J%0,%1) H_Dc(%0,74)
#define hcK:H_Sc(K%0,%1) H_Dc(%0,75)
#define hcL:H_Sc(L%0,%1) H_Dc(%0,76)
#define hcM:H_Sc(M%0,%1) H_Dc(%0,77)
#define hcN:H_Sc(N%0,%1) H_Dc(%0,78)
#define hcO:H_Sc(O%0,%1) H_Dc(%0,79)
#define hcP:H_Sc(P%0,%1) H_Dc(%0,80)
#define hcQ:H_Sc(Q%0,%1) H_Dc(%0,81)
#define hcR:H_Sc(R%0,%1) H_Dc(%0,82)
#define hcS:H_Sc(S%0,%1) H_Dc(%0,83)
#define hcT:H_Sc(T%0,%1) H_Dc(%0,84)
#define hcU:H_Sc(U%0,%1) H_Dc(%0,85)
#define hcV:H_Sc(V%0,%1) H_Dc(%0,86)
#define hcW:H_Sc(W%0,%1) H_Dc(%0,87)
#define hcX:H_Sc(X%0,%1) H_Dc(%0,88)
#define hcY:H_Sc(Y%0,%1) H_Dc(%0,89)
#define hcZ:H_Sc(Z%0,%1) H_Dc(%0,90)

#define hc0:H_Sc(0%0,%1) H_Dc(%0,48)
#define hc1:H_Sc(1%0,%1) H_Dc(%0,49)
#define hc2:H_Sc(2%0,%1) H_Dc(%0,50)
#define hc3:H_Sc(3%0,%1) H_Dc(%0,51)
#define hc4:H_Sc(4%0,%1) H_Dc(%0,52)
#define hc5:H_Sc(5%0,%1) H_Dc(%0,53)
#define hc6:H_Sc(6%0,%1) H_Dc(%0,54)
#define hc7:H_Sc(7%0,%1) H_Dc(%0,55)
#define hc8:H_Sc(8%0,%1) H_Dc(%0,56)
#define hc9:H_Sc(9%0,%1) H_Dc(%0,57)

#define hc_:H_Sc(_%0,%1) H_Dc(%0,95)
//#define hc@:H_Sc(@%0,%1) H_Dc(%0)

// Find the next character to test.
#define H_Nca(%0) hcb:H_Sc(%0,b)
#define H_Ncb(%0) hcc:H_Sc(%0,c)
#define H_Ncc(%0) hcd:H_Sc(%0,d)
#define H_Ncd(%0) hce:H_Sc(%0,e)
#define H_Nce(%0) hcf:H_Sc(%0,f)
#define H_Ncf(%0) hcg:H_Sc(%0,g)
#define H_Ncg(%0) hch:H_Sc(%0,h)
#define H_Nch(%0) hci:H_Sc(%0,i)
#define H_Nci(%0) hcj:H_Sc(%0,j)
#define H_Ncj(%0) hck:H_Sc(%0,k)
#define H_Nck(%0) hcl:H_Sc(%0,l)
#define H_Ncl(%0) hcm:H_Sc(%0,m)
#define H_Ncm(%0) hcn:H_Sc(%0,n)
#define H_Ncn(%0) hco:H_Sc(%0,o)
#define H_Nco(%0) hcp:H_Sc(%0,p)
#define H_Ncp(%0) hcq:H_Sc(%0,q)
#define H_Ncq(%0) hcr:H_Sc(%0,r)
#define H_Ncr(%0) hcs:H_Sc(%0,s)
#define H_Ncs(%0) hct:H_Sc(%0,t)
#define H_Nct(%0) hcu:H_Sc(%0,u)
#define H_Ncu(%0) hcv:H_Sc(%0,v)
#define H_Ncv(%0) hcw:H_Sc(%0,w)
#define H_Ncw(%0) hcx:H_Sc(%0,x)
#define H_Ncx(%0) hcy:H_Sc(%0,y)
#define H_Ncy(%0) hcz:H_Sc(%0,z)
#define H_Ncz(%0) hcA:H_Sc(%0,0)

#define H_NcA(%0) hcB:H_Sc(%0,B)
#define H_NcB(%0) hcC:H_Sc(%0,C)
#define H_NcC(%0) hcD:H_Sc(%0,D)
#define H_NcD(%0) hcE:H_Sc(%0,E)
#define H_NcE(%0) hcF:H_Sc(%0,F)
#define H_NcF(%0) hcG:H_Sc(%0,G)
#define H_NcG(%0) hcH:H_Sc(%0,H)
#define H_NcH(%0) hcI:H_Sc(%0,I)
#define H_NcI(%0) hcJ:H_Sc(%0,J)
#define H_NcJ(%0) hcK:H_Sc(%0,K)
#define H_NcK(%0) hcL:H_Sc(%0,L)
#define H_NcL(%0) hcM:H_Sc(%0,M)
#define H_NcM(%0) hcN:H_Sc(%0,N)
#define H_NcN(%0) hcO:H_Sc(%0,O)
#define H_NcO(%0) hcP:H_Sc(%0,P)
#define H_NcP(%0) hcQ:H_Sc(%0,Q)
#define H_NcQ(%0) hcR:H_Sc(%0,R)
#define H_NcR(%0) hcS:H_Sc(%0,S)
#define H_NcS(%0) hcT:H_Sc(%0,T)
#define H_NcT(%0) hcU:H_Sc(%0,U)
#define H_NcU(%0) hcV:H_Sc(%0,V)
#define H_NcV(%0) hcW:H_Sc(%0,W)
#define H_NcW(%0) hcX:H_Sc(%0,X)
#define H_NcX(%0) hcY:H_Sc(%0,Y)
#define H_NcY(%0) hcZ:H_Sc(%0,Z)
#define H_NcZ(%0) -1

#define H_Nc0(%0) hc1:H_Sc(%0,1)
#define H_Nc1(%0) hc2:H_Sc(%0,2)
#define H_Nc2(%0) hc3:H_Sc(%0,3)
#define H_Nc3(%0) hc4:H_Sc(%0,4)
#define H_Nc4(%0) hc5:H_Sc(%0,5)
#define H_Nc5(%0) hc6:H_Sc(%0,6)
#define H_Nc6(%0) hc7:H_Sc(%0,7)
#define H_Nc7(%0) hc8:H_Sc(%0,8)
#define H_Nc8(%0) hc9:H_Sc(%0,9)
#define H_Nc9(%0) hc_:H_Sc(%0,_)

#define H_Nc_(%0) hc0:H_Sc(%0,A)

// ===========
//  FNV1 hash 
// ===========

// ================
//  Case sensitive 
// ================

// Do the next character test as this one failed.
#define H_Sg(%0,%1) H_Ng%1(%0)
// End of string test failed.
#define H_Eg(%0)    hga:H_Sg(%0,a)
// Do the single addition.
#define H_Dg(%0,%1) (_:H_Rg(%0)*16777619^%1)
// Recurse through the string.
#define H_Rg(%0)    hg:H_Eg(%0)
// Test for the end of a string.
#define hg:H_Eg()   2166136261
// Find the length of a string at compile time.
//#define LEN(%0) _:(H_R(%0))

// Test for the current character.
#define hga:H_Sg(a%0,%1) H_Dg(%0,97)
#define hgb:H_Sg(b%0,%1) H_Dg(%0,98)
#define hgc:H_Sg(c%0,%1) H_Dg(%0,99)
#define hgd:H_Sg(d%0,%1) H_Dg(%0,100)
#define hge:H_Sg(e%0,%1) H_Dg(%0,101)
#define hgf:H_Sg(f%0,%1) H_Dg(%0,102)
#define hgg:H_Sg(g%0,%1) H_Dg(%0,103)
#define hgh:H_Sg(h%0,%1) H_Dg(%0,104)
#define hgi:H_Sg(i%0,%1) H_Dg(%0,105)
#define hgj:H_Sg(j%0,%1) H_Dg(%0,106)
#define hgk:H_Sg(k%0,%1) H_Dg(%0,107)
#define hgl:H_Sg(l%0,%1) H_Dg(%0,108)
#define hgm:H_Sg(m%0,%1) H_Dg(%0,109)
#define hgn:H_Sg(n%0,%1) H_Dg(%0,110)
#define hgo:H_Sg(o%0,%1) H_Dg(%0,111)
#define hgp:H_Sg(p%0,%1) H_Dg(%0,112)
#define hgq:H_Sg(q%0,%1) H_Dg(%0,113)
#define hgr:H_Sg(r%0,%1) H_Dg(%0,114)
#define hgs:H_Sg(s%0,%1) H_Dg(%0,115)
#define hgt:H_Sg(t%0,%1) H_Dg(%0,116)
#define hgu:H_Sg(u%0,%1) H_Dg(%0,117)
#define hgv:H_Sg(v%0,%1) H_Dg(%0,118)
#define hgw:H_Sg(w%0,%1) H_Dg(%0,119)
#define hgx:H_Sg(x%0,%1) H_Dg(%0,120)
#define hgy:H_Sg(y%0,%1) H_Dg(%0,121)
#define hgz:H_Sg(z%0,%1) H_Dg(%0,122)

#define hgA:H_Sg(A%0,%1) H_Dg(%0,65)
#define hgB:H_Sg(B%0,%1) H_Dg(%0,66)
#define hgC:H_Sg(C%0,%1) H_Dg(%0,67)
#define hgD:H_Sg(D%0,%1) H_Dg(%0,68)
#define hgE:H_Sg(E%0,%1) H_Dg(%0,69)
#define hgF:H_Sg(F%0,%1) H_Dg(%0,70)
#define hgG:H_Sg(G%0,%1) H_Dg(%0,71)
#define hgH:H_Sg(H%0,%1) H_Dg(%0,72)
#define hgI:H_Sg(I%0,%1) H_Dg(%0,73)
#define hgJ:H_Sg(J%0,%1) H_Dg(%0,74)
#define hgK:H_Sg(K%0,%1) H_Dg(%0,75)
#define hgL:H_Sg(L%0,%1) H_Dg(%0,76)
#define hgM:H_Sg(M%0,%1) H_Dg(%0,77)
#define hgN:H_Sg(N%0,%1) H_Dg(%0,78)
#define hgO:H_Sg(O%0,%1) H_Dg(%0,79)
#define hgP:H_Sg(P%0,%1) H_Dg(%0,80)
#define hgQ:H_Sg(Q%0,%1) H_Dg(%0,81)
#define hgR:H_Sg(R%0,%1) H_Dg(%0,82)
#define hgS:H_Sg(S%0,%1) H_Dg(%0,83)
#define hgT:H_Sg(T%0,%1) H_Dg(%0,84)
#define hgU:H_Sg(U%0,%1) H_Dg(%0,85)
#define hgV:H_Sg(V%0,%1) H_Dg(%0,86)
#define hgW:H_Sg(W%0,%1) H_Dg(%0,87)
#define hgX:H_Sg(X%0,%1) H_Dg(%0,88)
#define hgY:H_Sg(Y%0,%1) H_Dg(%0,89)
#define hgZ:H_Sg(Z%0,%1) H_Dg(%0,90)

#define hg0:H_Sg(0%0,%1) H_Dg(%0,48)
#define hg1:H_Sg(1%0,%1) H_Dg(%0,49)
#define hg2:H_Sg(2%0,%1) H_Dg(%0,50)
#define hg3:H_Sg(3%0,%1) H_Dg(%0,51)
#define hg4:H_Sg(4%0,%1) H_Dg(%0,52)
#define hg5:H_Sg(5%0,%1) H_Dg(%0,53)
#define hg6:H_Sg(6%0,%1) H_Dg(%0,54)
#define hg7:H_Sg(7%0,%1) H_Dg(%0,55)
#define hg8:H_Sg(8%0,%1) H_Dg(%0,56)
#define hg9:H_Sg(9%0,%1) H_Dg(%0,57)

#define hg_:H_Sg(_%0,%1) H_Dg(%0,95)
//#define hg@:H_Sg(@%0,%1) H_Dg(%0)

// Find the next character to test.
#define H_Nga(%0) hgb:H_Sg(%0,b)
#define H_Ngb(%0) hgc:H_Sg(%0,c)
#define H_Ngc(%0) hgd:H_Sg(%0,d)
#define H_Ngd(%0) hge:H_Sg(%0,e)
#define H_Nge(%0) hgf:H_Sg(%0,f)
#define H_Ngf(%0) hgg:H_Sg(%0,g)
#define H_Ngg(%0) hgh:H_Sg(%0,h)
#define H_Ngh(%0) hgi:H_Sg(%0,i)
#define H_Ngi(%0) hgj:H_Sg(%0,j)
#define H_Ngj(%0) hgk:H_Sg(%0,k)
#define H_Ngk(%0) hgl:H_Sg(%0,l)
#define H_Ngl(%0) hgm:H_Sg(%0,m)
#define H_Ngm(%0) hgn:H_Sg(%0,n)
#define H_Ngn(%0) hgo:H_Sg(%0,o)
#define H_Ngo(%0) hgp:H_Sg(%0,p)
#define H_Ngp(%0) hgq:H_Sg(%0,q)
#define H_Ngq(%0) hgr:H_Sg(%0,r)
#define H_Ngr(%0) hgs:H_Sg(%0,s)
#define H_Ngs(%0) hgt:H_Sg(%0,t)
#define H_Ngt(%0) hgu:H_Sg(%0,u)
#define H_Ngu(%0) hgv:H_Sg(%0,v)
#define H_Ngv(%0) hgw:H_Sg(%0,w)
#define H_Ngw(%0) hgx:H_Sg(%0,x)
#define H_Ngx(%0) hgy:H_Sg(%0,y)
#define H_Ngy(%0) hgz:H_Sg(%0,z)
#define H_Ngz(%0) hgA:H_Sg(%0,0)

#define H_NgA(%0) hgB:H_Sg(%0,B)
#define H_NgB(%0) hgC:H_Sg(%0,C)
#define H_NgC(%0) hgD:H_Sg(%0,D)
#define H_NgD(%0) hgE:H_Sg(%0,E)
#define H_NgE(%0) hgF:H_Sg(%0,F)
#define H_NgF(%0) hgG:H_Sg(%0,G)
#define H_NgG(%0) hgH:H_Sg(%0,H)
#define H_NgH(%0) hgI:H_Sg(%0,I)
#define H_NgI(%0) hgJ:H_Sg(%0,J)
#define H_NgJ(%0) hgK:H_Sg(%0,K)
#define H_NgK(%0) hgL:H_Sg(%0,L)
#define H_NgL(%0) hgM:H_Sg(%0,M)
#define H_NgM(%0) hgN:H_Sg(%0,N)
#define H_NgN(%0) hgO:H_Sg(%0,O)
#define H_NgO(%0) hgP:H_Sg(%0,P)
#define H_NgP(%0) hgQ:H_Sg(%0,Q)
#define H_NgQ(%0) hgR:H_Sg(%0,R)
#define H_NgR(%0) hgS:H_Sg(%0,S)
#define H_NgS(%0) hgT:H_Sg(%0,T)
#define H_NgT(%0) hgU:H_Sg(%0,U)
#define H_NgU(%0) hgV:H_Sg(%0,V)
#define H_NgV(%0) hgW:H_Sg(%0,W)
#define H_NgW(%0) hgX:H_Sg(%0,X)
#define H_NgX(%0) hgY:H_Sg(%0,Y)
#define H_NgY(%0) hgZ:H_Sg(%0,Z)
#define H_NgZ(%0) 2166136261

#define H_Ng0(%0) hg1:H_Sg(%0,1)
#define H_Ng1(%0) hg2:H_Sg(%0,2)
#define H_Ng2(%0) hg3:H_Sg(%0,3)
#define H_Ng3(%0) hg4:H_Sg(%0,4)
#define H_Ng4(%0) hg5:H_Sg(%0,5)
#define H_Ng5(%0) hg6:H_Sg(%0,6)
#define H_Ng6(%0) hg7:H_Sg(%0,7)
#define H_Ng7(%0) hg8:H_Sg(%0,8)
#define H_Ng8(%0) hg9:H_Sg(%0,9)
#define H_Ng9(%0) hg_:H_Sg(%0,_)

#define H_Ng_(%0) hg0:H_Sg(%0,A)

// ==================
//  Case insensitive 
// ==================

// Do the next character test as this one failed.
#define H_Sf(%0,%1) H_Nf%1(%0)
// End of string test failed.
#define H_Ef(%0)    hfa:H_Sf(%0,a)
// Do the single addition.
#define H_Df(%0,%1) (_:H_Rf(%0)*16777619^%1)
// Recurse through the string.
#define H_Rf(%0)    hf:H_Ef(%0)
// Test for the end of a string.
#define hf:H_Ef()   2166136261
// Find the length of a string at compile time.
//#define LEN(%0) _:(I_R(%0))

// Test for the current character.
#define hfa:H_Sf(a%0,%1) H_Df(%0,65)
#define hfb:H_Sf(b%0,%1) H_Df(%0,66)
#define hfc:H_Sf(c%0,%1) H_Df(%0,67)
#define hfd:H_Sf(d%0,%1) H_Df(%0,68)
#define hfe:H_Sf(e%0,%1) H_Df(%0,69)
#define hff:H_Sf(f%0,%1) H_Df(%0,70)
#define hfg:H_Sf(g%0,%1) H_Df(%0,71)
#define hfh:H_Sf(h%0,%1) H_Df(%0,72)
#define hfi:H_Sf(i%0,%1) H_Df(%0,73)
#define hfj:H_Sf(j%0,%1) H_Df(%0,74)
#define hfk:H_Sf(k%0,%1) H_Df(%0,75)
#define hfl:H_Sf(l%0,%1) H_Df(%0,76)
#define hfm:H_Sf(m%0,%1) H_Df(%0,77)
#define hfn:H_Sf(n%0,%1) H_Df(%0,78)
#define hfo:H_Sf(o%0,%1) H_Df(%0,79)
#define hfp:H_Sf(p%0,%1) H_Df(%0,80)
#define hfq:H_Sf(q%0,%1) H_Df(%0,81)
#define hfr:H_Sf(r%0,%1) H_Df(%0,82)
#define hfs:H_Sf(s%0,%1) H_Df(%0,83)
#define hft:H_Sf(t%0,%1) H_Df(%0,84)
#define hfu:H_Sf(u%0,%1) H_Df(%0,85)
#define hfv:H_Sf(v%0,%1) H_Df(%0,86)
#define hfw:H_Sf(w%0,%1) H_Df(%0,87)
#define hfx:H_Sf(x%0,%1) H_Df(%0,88)
#define hfy:H_Sf(y%0,%1) H_Df(%0,89)
#define hfz:H_Sf(z%0,%1) H_Df(%0,90)

#define hfA:H_Sf(A%0,%1) H_Df(%0,65)
#define hfB:H_Sf(B%0,%1) H_Df(%0,66)
#define hfC:H_Sf(C%0,%1) H_Df(%0,67)
#define hfD:H_Sf(D%0,%1) H_Df(%0,68)
#define hfE:H_Sf(E%0,%1) H_Df(%0,69)
#define hfF:H_Sf(F%0,%1) H_Df(%0,70)
#define hfG:H_Sf(G%0,%1) H_Df(%0,71)
#define hfH:H_Sf(H%0,%1) H_Df(%0,72)
#define hfI:H_Sf(I%0,%1) H_Df(%0,73)
#define hfJ:H_Sf(J%0,%1) H_Df(%0,74)
#define hfK:H_Sf(K%0,%1) H_Df(%0,75)
#define hfL:H_Sf(L%0,%1) H_Df(%0,76)
#define hfM:H_Sf(M%0,%1) H_Df(%0,77)
#define hfN:H_Sf(N%0,%1) H_Df(%0,78)
#define hfO:H_Sf(O%0,%1) H_Df(%0,79)
#define hfP:H_Sf(P%0,%1) H_Df(%0,80)
#define hfQ:H_Sf(Q%0,%1) H_Df(%0,81)
#define hfR:H_Sf(R%0,%1) H_Df(%0,82)
#define hfS:H_Sf(S%0,%1) H_Df(%0,83)
#define hfT:H_Sf(T%0,%1) H_Df(%0,84)
#define hfU:H_Sf(U%0,%1) H_Df(%0,85)
#define hfV:H_Sf(V%0,%1) H_Df(%0,86)
#define hfW:H_Sf(W%0,%1) H_Df(%0,87)
#define hfX:H_Sf(X%0,%1) H_Df(%0,88)
#define hfY:H_Sf(Y%0,%1) H_Df(%0,89)
#define hfZ:H_Sf(Z%0,%1) H_Df(%0,90)

#define hf0:H_Sf(0%0,%1) H_Df(%0,48)
#define hf1:H_Sf(1%0,%1) H_Df(%0,49)
#define hf2:H_Sf(2%0,%1) H_Df(%0,50)
#define hf3:H_Sf(3%0,%1) H_Df(%0,51)
#define hf4:H_Sf(4%0,%1) H_Df(%0,52)
#define hf5:H_Sf(5%0,%1) H_Df(%0,53)
#define hf6:H_Sf(6%0,%1) H_Df(%0,54)
#define hf7:H_Sf(7%0,%1) H_Df(%0,55)
#define hf8:H_Sf(8%0,%1) H_Df(%0,56)
#define hf9:H_Sf(9%0,%1) H_Df(%0,57)

#define hf_:H_Sf(_%0,%1) H_Df(%0,95)
//#define hf@:H_Sf(@%0,%1) H_Df(%0)

// Find the next character to test.
#define H_Nfa(%0) hfb:H_Sf(%0,b)
#define H_Nfb(%0) hfc:H_Sf(%0,c)
#define H_Nfc(%0) hfd:H_Sf(%0,d)
#define H_Nfd(%0) hfe:H_Sf(%0,e)
#define H_Nfe(%0) hff:H_Sf(%0,f)
#define H_Nff(%0) hfg:H_Sf(%0,g)
#define H_Nfg(%0) hfh:H_Sf(%0,h)
#define H_Nfh(%0) hfi:H_Sf(%0,i)
#define H_Nfi(%0) hfj:H_Sf(%0,j)
#define H_Nfj(%0) hfk:H_Sf(%0,k)
#define H_Nfk(%0) hfl:H_Sf(%0,l)
#define H_Nfl(%0) hfm:H_Sf(%0,m)
#define H_Nfm(%0) hfn:H_Sf(%0,n)
#define H_Nfn(%0) hfo:H_Sf(%0,o)
#define H_Nfo(%0) hfp:H_Sf(%0,p)
#define H_Nfp(%0) hfq:H_Sf(%0,q)
#define H_Nfq(%0) hfr:H_Sf(%0,r)
#define H_Nfr(%0) hfs:H_Sf(%0,s)
#define H_Nfs(%0) hft:H_Sf(%0,t)
#define H_Nft(%0) hfu:H_Sf(%0,u)
#define H_Nfu(%0) hfv:H_Sf(%0,v)
#define H_Nfv(%0) hfw:H_Sf(%0,w)
#define H_Nfw(%0) hfx:H_Sf(%0,x)
#define H_Nfx(%0) hfy:H_Sf(%0,y)
#define H_Nfy(%0) hfz:H_Sf(%0,z)
#define H_Nfz(%0) hfA:H_Sf(%0,0)

#define H_NfA(%0) hfB:H_Sf(%0,B)
#define H_NfB(%0) hfC:H_Sf(%0,C)
#define H_NfC(%0) hfD:H_Sf(%0,D)
#define H_NfD(%0) hfE:H_Sf(%0,E)
#define H_NfE(%0) hfF:H_Sf(%0,F)
#define H_NfF(%0) hfG:H_Sf(%0,G)
#define H_NfG(%0) hfH:H_Sf(%0,H)
#define H_NfH(%0) hfI:H_Sf(%0,I)
#define H_NfI(%0) hfJ:H_Sf(%0,J)
#define H_NfJ(%0) hfK:H_Sf(%0,K)
#define H_NfK(%0) hfL:H_Sf(%0,L)
#define H_NfL(%0) hfM:H_Sf(%0,M)
#define H_NfM(%0) hfN:H_Sf(%0,N)
#define H_NfN(%0) hfO:H_Sf(%0,O)
#define H_NfO(%0) hfP:H_Sf(%0,P)
#define H_NfP(%0) hfQ:H_Sf(%0,Q)
#define H_NfQ(%0) hfR:H_Sf(%0,R)
#define H_NfR(%0) hfS:H_Sf(%0,S)
#define H_NfS(%0) hfT:H_Sf(%0,T)
#define H_NfT(%0) hfU:H_Sf(%0,U)
#define H_NfU(%0) hfV:H_Sf(%0,V)
#define H_NfV(%0) hfW:H_Sf(%0,W)
#define H_NfW(%0) hfX:H_Sf(%0,X)
#define H_NfX(%0) hfY:H_Sf(%0,Y)
#define H_NfY(%0) hfZ:H_Sf(%0,Z)
#define H_NfZ(%0) 2166136261

#define H_Nf0(%0) hf1:H_Sf(%0,1)
#define H_Nf1(%0) hf2:H_Sf(%0,2)
#define H_Nf2(%0) hf3:H_Sf(%0,3)
#define H_Nf3(%0) hf4:H_Sf(%0,4)
#define H_Nf4(%0) hf5:H_Sf(%0,5)
#define H_Nf5(%0) hf6:H_Sf(%0,6)
#define H_Nf6(%0) hf7:H_Sf(%0,7)
#define H_Nf7(%0) hf8:H_Sf(%0,8)
#define H_Nf8(%0) hf9:H_Sf(%0,9)
#define H_Nf9(%0) hf_:H_Sf(%0,_)

#define H_Nf_(%0) hf0:H_Sf(%0,A)

// ============
//  FNV1a hash 
// ============

// ================
//  Case sensitive 
// ================

// Do the next character test as this one failed.
#define H_Sa(%0,%1) H_Na%1(%0)
// End of string test failed.
#define H_Ea(%0)    haa:H_Sa(%0,a)
// Do the single addition.
#define H_Da(%0,%1) ((_:H_Ra(%0)^%1)*16777619)
// Recurse through the string.
#define H_Ra(%0)    ha:H_Ea(%0)
// Test for the end of a string.
#define ha:H_Ea()   2166136261
// Find the length of a string at compile time.
//#define LEN(%0) _:(H_R(%0))

// Test for the current character.
#define haa:H_Sa(a%0,%1) H_Da(%0,97)
#define hab:H_Sa(b%0,%1) H_Da(%0,98)
#define hac:H_Sa(c%0,%1) H_Da(%0,99)
#define had:H_Sa(d%0,%1) H_Da(%0,100)
#define hae:H_Sa(e%0,%1) H_Da(%0,101)
#define haf:H_Sa(f%0,%1) H_Da(%0,102)
#define hag:H_Sa(g%0,%1) H_Da(%0,103)
#define hah:H_Sa(h%0,%1) H_Da(%0,104)
#define hai:H_Sa(i%0,%1) H_Da(%0,105)
#define haj:H_Sa(j%0,%1) H_Da(%0,106)
#define hak:H_Sa(k%0,%1) H_Da(%0,107)
#define hal:H_Sa(l%0,%1) H_Da(%0,108)
#define ham:H_Sa(m%0,%1) H_Da(%0,109)
#define han:H_Sa(n%0,%1) H_Da(%0,110)
#define hao:H_Sa(o%0,%1) H_Da(%0,111)
#define hap:H_Sa(p%0,%1) H_Da(%0,112)
#define haq:H_Sa(q%0,%1) H_Da(%0,113)
#define har:H_Sa(r%0,%1) H_Da(%0,114)
#define has:H_Sa(s%0,%1) H_Da(%0,115)
#define hat:H_Sa(t%0,%1) H_Da(%0,116)
#define hau:H_Sa(u%0,%1) H_Da(%0,117)
#define hav:H_Sa(v%0,%1) H_Da(%0,118)
#define haw:H_Sa(w%0,%1) H_Da(%0,119)
#define hax:H_Sa(x%0,%1) H_Da(%0,120)
#define hay:H_Sa(y%0,%1) H_Da(%0,121)
#define haz:H_Sa(z%0,%1) H_Da(%0,122)

#define haA:H_Sa(A%0,%1) H_Da(%0,65)
#define haB:H_Sa(B%0,%1) H_Da(%0,66)
#define haC:H_Sa(C%0,%1) H_Da(%0,67)
#define haD:H_Sa(D%0,%1) H_Da(%0,68)
#define haE:H_Sa(E%0,%1) H_Da(%0,69)
#define haF:H_Sa(F%0,%1) H_Da(%0,70)
#define haG:H_Sa(G%0,%1) H_Da(%0,71)
#define haH:H_Sa(H%0,%1) H_Da(%0,72)
#define haI:H_Sa(I%0,%1) H_Da(%0,73)
#define haJ:H_Sa(J%0,%1) H_Da(%0,74)
#define haK:H_Sa(K%0,%1) H_Da(%0,75)
#define haL:H_Sa(L%0,%1) H_Da(%0,76)
#define haM:H_Sa(M%0,%1) H_Da(%0,77)
#define haN:H_Sa(N%0,%1) H_Da(%0,78)
#define haO:H_Sa(O%0,%1) H_Da(%0,79)
#define haP:H_Sa(P%0,%1) H_Da(%0,80)
#define haQ:H_Sa(Q%0,%1) H_Da(%0,81)
#define haR:H_Sa(R%0,%1) H_Da(%0,82)
#define haS:H_Sa(S%0,%1) H_Da(%0,83)
#define haT:H_Sa(T%0,%1) H_Da(%0,84)
#define haU:H_Sa(U%0,%1) H_Da(%0,85)
#define haV:H_Sa(V%0,%1) H_Da(%0,86)
#define haW:H_Sa(W%0,%1) H_Da(%0,87)
#define haX:H_Sa(X%0,%1) H_Da(%0,88)
#define haY:H_Sa(Y%0,%1) H_Da(%0,89)
#define haZ:H_Sa(Z%0,%1) H_Da(%0,90)

#define ha0:H_Sa(0%0,%1) H_Da(%0,48)
#define ha1:H_Sa(1%0,%1) H_Da(%0,49)
#define ha2:H_Sa(2%0,%1) H_Da(%0,50)
#define ha3:H_Sa(3%0,%1) H_Da(%0,51)
#define ha4:H_Sa(4%0,%1) H_Da(%0,52)
#define ha5:H_Sa(5%0,%1) H_Da(%0,53)
#define ha6:H_Sa(6%0,%1) H_Da(%0,54)
#define ha7:H_Sa(7%0,%1) H_Da(%0,55)
#define ha8:H_Sa(8%0,%1) H_Da(%0,56)
#define ha9:H_Sa(9%0,%1) H_Da(%0,57)

#define ha_:H_Sa(_%0,%1) H_Da(%0,95)
//#define ha@:H_Sa(@%0,%1) H_Da(%0)

// Find the next character to test.
#define H_Naa(%0) hab:H_Sa(%0,b)
#define H_Nab(%0) hac:H_Sa(%0,c)
#define H_Nac(%0) had:H_Sa(%0,d)
#define H_Nad(%0) hae:H_Sa(%0,e)
#define H_Nae(%0) haf:H_Sa(%0,f)
#define H_Naf(%0) hag:H_Sa(%0,g)
#define H_Nag(%0) hah:H_Sa(%0,h)
#define H_Nah(%0) hai:H_Sa(%0,i)
#define H_Nai(%0) haj:H_Sa(%0,j)
#define H_Naj(%0) hak:H_Sa(%0,k)
#define H_Nak(%0) hal:H_Sa(%0,l)
#define H_Nal(%0) ham:H_Sa(%0,m)
#define H_Nam(%0) han:H_Sa(%0,n)
#define H_Nan(%0) hao:H_Sa(%0,o)
#define H_Nao(%0) hap:H_Sa(%0,p)
#define H_Nap(%0) haq:H_Sa(%0,q)
#define H_Naq(%0) har:H_Sa(%0,r)
#define H_Nar(%0) has:H_Sa(%0,s)
#define H_Nas(%0) hat:H_Sa(%0,t)
#define H_Nat(%0) hau:H_Sa(%0,u)
#define H_Nau(%0) hav:H_Sa(%0,v)
#define H_Nav(%0) haw:H_Sa(%0,w)
#define H_Naw(%0) hax:H_Sa(%0,x)
#define H_Nax(%0) hay:H_Sa(%0,y)
#define H_Nay(%0) haz:H_Sa(%0,z)
#define H_Naz(%0) haA:H_Sa(%0,0)

#define H_NaA(%0) haB:H_Sa(%0,B)
#define H_NaB(%0) haC:H_Sa(%0,C)
#define H_NaC(%0) haD:H_Sa(%0,D)
#define H_NaD(%0) haE:H_Sa(%0,E)
#define H_NaE(%0) haF:H_Sa(%0,F)
#define H_NaF(%0) haG:H_Sa(%0,G)
#define H_NaG(%0) haH:H_Sa(%0,H)
#define H_NaH(%0) haI:H_Sa(%0,I)
#define H_NaI(%0) haJ:H_Sa(%0,J)
#define H_NaJ(%0) haK:H_Sa(%0,K)
#define H_NaK(%0) haL:H_Sa(%0,L)
#define H_NaL(%0) haM:H_Sa(%0,M)
#define H_NaM(%0) haN:H_Sa(%0,N)
#define H_NaN(%0) haO:H_Sa(%0,O)
#define H_NaO(%0) haP:H_Sa(%0,P)
#define H_NaP(%0) haQ:H_Sa(%0,Q)
#define H_NaQ(%0) haR:H_Sa(%0,R)
#define H_NaR(%0) haS:H_Sa(%0,S)
#define H_NaS(%0) haT:H_Sa(%0,T)
#define H_NaT(%0) haU:H_Sa(%0,U)
#define H_NaU(%0) haV:H_Sa(%0,V)
#define H_NaV(%0) haW:H_Sa(%0,W)
#define H_NaW(%0) haX:H_Sa(%0,X)
#define H_NaX(%0) haY:H_Sa(%0,Y)
#define H_NaY(%0) haZ:H_Sa(%0,Z)
#define H_NaZ(%0) 2166136261

#define H_Na0(%0) ha1:H_Sa(%0,1)
#define H_Na1(%0) ha2:H_Sa(%0,2)
#define H_Na2(%0) ha3:H_Sa(%0,3)
#define H_Na3(%0) ha4:H_Sa(%0,4)
#define H_Na4(%0) ha5:H_Sa(%0,5)
#define H_Na5(%0) ha6:H_Sa(%0,6)
#define H_Na6(%0) ha7:H_Sa(%0,7)
#define H_Na7(%0) ha8:H_Sa(%0,8)
#define H_Na8(%0) ha9:H_Sa(%0,9)
#define H_Na9(%0) ha_:H_Sa(%0,_)

#define H_Na_(%0) ha0:H_Sa(%0,A)

// ==================
//  Case insensitive 
// ==================

// Do the next character test as this one failed.
#define H_Sd(%0,%1) H_Nd%1(%0)
// End of string test failed.
#define H_Ed(%0)    hda:H_Sd(%0,a)
// Do the single addition.
#define H_Dd(%0,%1) ((_:H_Rd(%0)^%1)*16777619)
// Recurse through the string.
#define H_Rd(%0)    hd:H_Ed(%0)
// Test for the end of a string.
#define hd:H_Ed()   2166136261
// Find the length of a string at compile time.
//#define LEN(%0) _:(I_R(%0))

// Test for the current character.
#define hda:H_Sd(a%0,%1) H_Dd(%0,65)
#define hdb:H_Sd(b%0,%1) H_Dd(%0,66)
#define hdc:H_Sd(c%0,%1) H_Dd(%0,67)
#define hdd:H_Sd(d%0,%1) H_Dd(%0,68)
#define hde:H_Sd(e%0,%1) H_Dd(%0,69)
#define hdf:H_Sd(f%0,%1) H_Dd(%0,70)
#define hdg:H_Sd(g%0,%1) H_Dd(%0,71)
#define hdh:H_Sd(h%0,%1) H_Dd(%0,72)
#define hdi:H_Sd(i%0,%1) H_Dd(%0,73)
#define hdj:H_Sd(j%0,%1) H_Dd(%0,74)
#define hdk:H_Sd(k%0,%1) H_Dd(%0,75)
#define hdl:H_Sd(l%0,%1) H_Dd(%0,76)
#define hdm:H_Sd(m%0,%1) H_Dd(%0,77)
#define hdn:H_Sd(n%0,%1) H_Dd(%0,78)
#define hdo:H_Sd(o%0,%1) H_Dd(%0,79)
#define hdp:H_Sd(p%0,%1) H_Dd(%0,80)
#define hdq:H_Sd(q%0,%1) H_Dd(%0,81)
#define hdr:H_Sd(r%0,%1) H_Dd(%0,82)
#define hds:H_Sd(s%0,%1) H_Dd(%0,83)
#define hdt:H_Sd(t%0,%1) H_Dd(%0,84)
#define hdu:H_Sd(u%0,%1) H_Dd(%0,85)
#define hdv:H_Sd(v%0,%1) H_Dd(%0,86)
#define hdw:H_Sd(w%0,%1) H_Dd(%0,87)
#define hdx:H_Sd(x%0,%1) H_Dd(%0,88)
#define hdy:H_Sd(y%0,%1) H_Dd(%0,89)
#define hdz:H_Sd(z%0,%1) H_Dd(%0,90)

#define hdA:H_Sd(A%0,%1) H_Dd(%0,65)
#define hdB:H_Sd(B%0,%1) H_Dd(%0,66)
#define hdC:H_Sd(C%0,%1) H_Dd(%0,67)
#define hdD:H_Sd(D%0,%1) H_Dd(%0,68)
#define hdE:H_Sd(E%0,%1) H_Dd(%0,69)
#define hdF:H_Sd(F%0,%1) H_Dd(%0,70)
#define hdG:H_Sd(G%0,%1) H_Dd(%0,71)
#define hdH:H_Sd(H%0,%1) H_Dd(%0,72)
#define hdI:H_Sd(I%0,%1) H_Dd(%0,73)
#define hdJ:H_Sd(J%0,%1) H_Dd(%0,74)
#define hdK:H_Sd(K%0,%1) H_Dd(%0,75)
#define hdL:H_Sd(L%0,%1) H_Dd(%0,76)
#define hdM:H_Sd(M%0,%1) H_Dd(%0,77)
#define hdN:H_Sd(N%0,%1) H_Dd(%0,78)
#define hdO:H_Sd(O%0,%1) H_Dd(%0,79)
#define hdP:H_Sd(P%0,%1) H_Dd(%0,80)
#define hdQ:H_Sd(Q%0,%1) H_Dd(%0,81)
#define hdR:H_Sd(R%0,%1) H_Dd(%0,82)
#define hdS:H_Sd(S%0,%1) H_Dd(%0,83)
#define hdT:H_Sd(T%0,%1) H_Dd(%0,84)
#define hdU:H_Sd(U%0,%1) H_Dd(%0,85)
#define hdV:H_Sd(V%0,%1) H_Dd(%0,86)
#define hdW:H_Sd(W%0,%1) H_Dd(%0,87)
#define hdX:H_Sd(X%0,%1) H_Dd(%0,88)
#define hdY:H_Sd(Y%0,%1) H_Dd(%0,89)
#define hdZ:H_Sd(Z%0,%1) H_Dd(%0,90)

#define hd0:H_Sd(0%0,%1) H_Dd(%0,48)
#define hd1:H_Sd(1%0,%1) H_Dd(%0,49)
#define hd2:H_Sd(2%0,%1) H_Dd(%0,50)
#define hd3:H_Sd(3%0,%1) H_Dd(%0,51)
#define hd4:H_Sd(4%0,%1) H_Dd(%0,52)
#define hd5:H_Sd(5%0,%1) H_Dd(%0,53)
#define hd6:H_Sd(6%0,%1) H_Dd(%0,54)
#define hd7:H_Sd(7%0,%1) H_Dd(%0,55)
#define hd8:H_Sd(8%0,%1) H_Dd(%0,56)
#define hd9:H_Sd(9%0,%1) H_Dd(%0,57)

#define hd_:H_Sd(_%0,%1) H_Dd(%0,95)
//#define hd@:H_Sd(@%0,%1) H_Dd(%0)

// Find the next character to test.
#define H_Nda(%0) hdb:H_Sd(%0,b)
#define H_Ndb(%0) hdc:H_Sd(%0,c)
#define H_Ndc(%0) hdd:H_Sd(%0,d)
#define H_Ndd(%0) hde:H_Sd(%0,e)
#define H_Nde(%0) hdf:H_Sd(%0,f)
#define H_Ndf(%0) hdg:H_Sd(%0,g)
#define H_Ndg(%0) hdh:H_Sd(%0,h)
#define H_Ndh(%0) hdi:H_Sd(%0,i)
#define H_Ndi(%0) hdj:H_Sd(%0,j)
#define H_Ndj(%0) hdk:H_Sd(%0,k)
#define H_Ndk(%0) hdl:H_Sd(%0,l)
#define H_Ndl(%0) hdm:H_Sd(%0,m)
#define H_Ndm(%0) hdn:H_Sd(%0,n)
#define H_Ndn(%0) hdo:H_Sd(%0,o)
#define H_Ndo(%0) hdp:H_Sd(%0,p)
#define H_Ndp(%0) hdq:H_Sd(%0,q)
#define H_Ndq(%0) hdr:H_Sd(%0,r)
#define H_Ndr(%0) hds:H_Sd(%0,s)
#define H_Nds(%0) hdt:H_Sd(%0,t)
#define H_Ndt(%0) hdu:H_Sd(%0,u)
#define H_Ndu(%0) hdv:H_Sd(%0,v)
#define H_Ndv(%0) hdw:H_Sd(%0,w)
#define H_Ndw(%0) hdx:H_Sd(%0,x)
#define H_Ndx(%0) hdy:H_Sd(%0,y)
#define H_Ndy(%0) hdz:H_Sd(%0,z)
#define H_Ndz(%0) hdA:H_Sd(%0,0)

#define H_NdA(%0) hdB:H_Sd(%0,B)
#define H_NdB(%0) hdC:H_Sd(%0,C)
#define H_NdC(%0) hdD:H_Sd(%0,D)
#define H_NdD(%0) hdE:H_Sd(%0,E)
#define H_NdE(%0) hdF:H_Sd(%0,F)
#define H_NdF(%0) hdG:H_Sd(%0,G)
#define H_NdG(%0) hdH:H_Sd(%0,H)
#define H_NdH(%0) hdI:H_Sd(%0,I)
#define H_NdI(%0) hdJ:H_Sd(%0,J)
#define H_NdJ(%0) hdK:H_Sd(%0,K)
#define H_NdK(%0) hdL:H_Sd(%0,L)
#define H_NdL(%0) hdM:H_Sd(%0,M)
#define H_NdM(%0) hdN:H_Sd(%0,N)
#define H_NdN(%0) hdO:H_Sd(%0,O)
#define H_NdO(%0) hdP:H_Sd(%0,P)
#define H_NdP(%0) hdQ:H_Sd(%0,Q)
#define H_NdQ(%0) hdR:H_Sd(%0,R)
#define H_NdR(%0) hdS:H_Sd(%0,S)
#define H_NdS(%0) hdT:H_Sd(%0,T)
#define H_NdT(%0) hdU:H_Sd(%0,U)
#define H_NdU(%0) hdV:H_Sd(%0,V)
#define H_NdV(%0) hdW:H_Sd(%0,W)
#define H_NdW(%0) hdX:H_Sd(%0,X)
#define H_NdX(%0) hdY:H_Sd(%0,Y)
#define H_NdY(%0) hdZ:H_Sd(%0,Z)
#define H_NdZ(%0) 2166136261

#define H_Nd0(%0) hd1:H_Sd(%0,1)
#define H_Nd1(%0) hd2:H_Sd(%0,2)
#define H_Nd2(%0) hd3:H_Sd(%0,3)
#define H_Nd3(%0) hd4:H_Sd(%0,4)
#define H_Nd4(%0) hd5:H_Sd(%0,5)
#define H_Nd5(%0) hd6:H_Sd(%0,6)
#define H_Nd6(%0) hd7:H_Sd(%0,7)
#define H_Nd7(%0) hd8:H_Sd(%0,8)
#define H_Nd8(%0) hd9:H_Sd(%0,9)
#define H_Nd9(%0) hd_:H_Sd(%0,_)

#define H_Nd_(%0) hd0:H_Sd(%0,A)

// =============
//  Old version 
// =============

// ================
//  Case sensitive 
// ================

// These are the default values
//#define HASH(%0,%1) HASH@%0(%1)

/*#define _H@b HASH@bernstein
#define _H@f HASH@fnv1
#define _H@a HASH@fnv1a*/

// ================
//  Bernstein hash 
// ================

// Signify the end with two "@" symbols.
#define HASH@bernstein(%0) _REHASH@b(%0,@,@)

// Internal call.
#define _REHASH@b(%0,%1) _HASH@b_%0(%1)

// The bit that actually does the work.
#define _DOHASH@b(%0,%1,%2) (_HASH@b_%1(%2)*33+%0)

// Space.
#define _HASH@b_(%0) _DOHASH@b(32,%0)

// Numbers.
#define _HASH@b_0(%0) _DOHASH@b(48,%0)
#define _HASH@b_1(%0) _DOHASH@b(49,%0)
#define _HASH@b_2(%0) _DOHASH@b(50,%0)
#define _HASH@b_3(%0) _DOHASH@b(51,%0)
#define _HASH@b_4(%0) _DOHASH@b(52,%0)
#define _HASH@b_5(%0) _DOHASH@b(53,%0)
#define _HASH@b_6(%0) _DOHASH@b(54,%0)
#define _HASH@b_7(%0) _DOHASH@b(55,%0)
#define _HASH@b_8(%0) _DOHASH@b(56,%0)
#define _HASH@b_9(%0) _DOHASH@b(57,%0)

// Upper case letters.
#define _HASH@b_A(%0) _DOHASH@b(65,%0)
#define _HASH@b_B(%0) _DOHASH@b(66,%0)
#define _HASH@b_C(%0) _DOHASH@b(67,%0)
#define _HASH@b_D(%0) _DOHASH@b(68,%0)
#define _HASH@b_E(%0) _DOHASH@b(69,%0)
#define _HASH@b_F(%0) _DOHASH@b(70,%0)
#define _HASH@b_G(%0) _DOHASH@b(71,%0)
#define _HASH@b_H(%0) _DOHASH@b(72,%0)
#define _HASH@b_I(%0) _DOHASH@b(73,%0)
#define _HASH@b_J(%0) _DOHASH@b(74,%0)
#define _HASH@b_K(%0) _DOHASH@b(75,%0)
#define _HASH@b_L(%0) _DOHASH@b(76,%0)
#define _HASH@b_M(%0) _DOHASH@b(77,%0)
#define _HASH@b_N(%0) _DOHASH@b(78,%0)
#define _HASH@b_O(%0) _DOHASH@b(79,%0)
#define _HASH@b_P(%0) _DOHASH@b(80,%0)
#define _HASH@b_Q(%0) _DOHASH@b(81,%0)
#define _HASH@b_R(%0) _DOHASH@b(82,%0)
#define _HASH@b_S(%0) _DOHASH@b(83,%0)
#define _HASH@b_T(%0) _DOHASH@b(84,%0)
#define _HASH@b_U(%0) _DOHASH@b(85,%0)
#define _HASH@b_V(%0) _DOHASH@b(86,%0)
#define _HASH@b_W(%0) _DOHASH@b(87,%0)
#define _HASH@b_X(%0) _DOHASH@b(88,%0)
#define _HASH@b_Y(%0) _DOHASH@b(89,%0)
#define _HASH@b_Z(%0) _DOHASH@b(90,%0)

// Underscore.
#define _HASH@b__(%0) _DOHASH@b(95,%0)

// Lower case letters.
#define _HASH@b_a(%0) _DOHASH@b(97,%0)
#define _HASH@b_b(%0) _DOHASH@b(98,%0)
#define _HASH@b_c(%0) _DOHASH@b(99,%0)
#define _HASH@b_d(%0) _DOHASH@b(100,%0)
#define _HASH@b_e(%0) _DOHASH@b(101,%0)
#define _HASH@b_f(%0) _DOHASH@b(102,%0)
#define _HASH@b_g(%0) _DOHASH@b(103,%0)
#define _HASH@b_h(%0) _DOHASH@b(104,%0)
#define _HASH@b_i(%0) _DOHASH@b(105,%0)
#define _HASH@b_j(%0) _DOHASH@b(106,%0)
#define _HASH@b_k(%0) _DOHASH@b(107,%0)
#define _HASH@b_l(%0) _DOHASH@b(108,%0)
#define _HASH@b_m(%0) _DOHASH@b(109,%0)
#define _HASH@b_n(%0) _DOHASH@b(110,%0)
#define _HASH@b_o(%0) _DOHASH@b(111,%0)
#define _HASH@b_p(%0) _DOHASH@b(112,%0)
#define _HASH@b_q(%0) _DOHASH@b(113,%0)
#define _HASH@b_r(%0) _DOHASH@b(114,%0)
#define _HASH@b_s(%0) _DOHASH@b(115,%0)
#define _HASH@b_t(%0) _DOHASH@b(116,%0)
#define _HASH@b_u(%0) _DOHASH@b(117,%0)
#define _HASH@b_v(%0) _DOHASH@b(118,%0)
#define _HASH@b_w(%0) _DOHASH@b(119,%0)
#define _HASH@b_x(%0) _DOHASH@b(120,%0)
#define _HASH@b_y(%0) _DOHASH@b(121,%0)
#define _HASH@b_z(%0) _DOHASH@b(122,%0)

// String end.
#define _HASH@b_@(%0) -1

// ===========
//  FNV1 hash 
// ===========

// Signify the end with two "@" symbols.
#define HASH@fnv1(%0) _REHASH@f(%0,@,@)

// Internal call.
#define _REHASH@f(%0,%1) _HASH@f_%0(%1)

// The bit that actually does the work.
#define _DOHASH@f(%0,%1,%2) (_HASH@f_%1(%2)*16777619^%0)

// Space.
#define _HASH@f_(%0) _DOHASH@f(32,%0)

// Numbers.
#define _HASH@f_0(%0) _DOHASH@f(48,%0)
#define _HASH@f_1(%0) _DOHASH@f(49,%0)
#define _HASH@f_2(%0) _DOHASH@f(50,%0)
#define _HASH@f_3(%0) _DOHASH@f(51,%0)
#define _HASH@f_4(%0) _DOHASH@f(52,%0)
#define _HASH@f_5(%0) _DOHASH@f(53,%0)
#define _HASH@f_6(%0) _DOHASH@f(54,%0)
#define _HASH@f_7(%0) _DOHASH@f(55,%0)
#define _HASH@f_8(%0) _DOHASH@f(56,%0)
#define _HASH@f_9(%0) _DOHASH@f(57,%0)

// Upper case letters.
#define _HASH@f_A(%0) _DOHASH@f(65,%0)
#define _HASH@f_B(%0) _DOHASH@f(66,%0)
#define _HASH@f_C(%0) _DOHASH@f(67,%0)
#define _HASH@f_D(%0) _DOHASH@f(68,%0)
#define _HASH@f_E(%0) _DOHASH@f(69,%0)
#define _HASH@f_F(%0) _DOHASH@f(70,%0)
#define _HASH@f_G(%0) _DOHASH@f(71,%0)
#define _HASH@f_H(%0) _DOHASH@f(72,%0)
#define _HASH@f_I(%0) _DOHASH@f(73,%0)
#define _HASH@f_J(%0) _DOHASH@f(74,%0)
#define _HASH@f_K(%0) _DOHASH@f(75,%0)
#define _HASH@f_L(%0) _DOHASH@f(76,%0)
#define _HASH@f_M(%0) _DOHASH@f(77,%0)
#define _HASH@f_N(%0) _DOHASH@f(78,%0)
#define _HASH@f_O(%0) _DOHASH@f(79,%0)
#define _HASH@f_P(%0) _DOHASH@f(80,%0)
#define _HASH@f_Q(%0) _DOHASH@f(81,%0)
#define _HASH@f_R(%0) _DOHASH@f(82,%0)
#define _HASH@f_S(%0) _DOHASH@f(83,%0)
#define _HASH@f_T(%0) _DOHASH@f(84,%0)
#define _HASH@f_U(%0) _DOHASH@f(85,%0)
#define _HASH@f_V(%0) _DOHASH@f(86,%0)
#define _HASH@f_W(%0) _DOHASH@f(87,%0)
#define _HASH@f_X(%0) _DOHASH@f(88,%0)
#define _HASH@f_Y(%0) _DOHASH@f(89,%0)
#define _HASH@f_Z(%0) _DOHASH@f(90,%0)

// Underscore.
#define _HASH@f__(%0) _DOHASH@f(95,%0)

// Lower case letters.
#define _HASH@f_a(%0) _DOHASH@f(97,%0)
#define _HASH@f_b(%0) _DOHASH@f(98,%0)
#define _HASH@f_c(%0) _DOHASH@f(99,%0)
#define _HASH@f_d(%0) _DOHASH@f(100,%0)
#define _HASH@f_e(%0) _DOHASH@f(101,%0)
#define _HASH@f_f(%0) _DOHASH@f(102,%0)
#define _HASH@f_g(%0) _DOHASH@f(103,%0)
#define _HASH@f_h(%0) _DOHASH@f(104,%0)
#define _HASH@f_i(%0) _DOHASH@f(105,%0)
#define _HASH@f_j(%0) _DOHASH@f(106,%0)
#define _HASH@f_k(%0) _DOHASH@f(107,%0)
#define _HASH@f_l(%0) _DOHASH@f(108,%0)
#define _HASH@f_m(%0) _DOHASH@f(109,%0)
#define _HASH@f_n(%0) _DOHASH@f(110,%0)
#define _HASH@f_o(%0) _DOHASH@f(111,%0)
#define _HASH@f_p(%0) _DOHASH@f(112,%0)
#define _HASH@f_q(%0) _DOHASH@f(113,%0)
#define _HASH@f_r(%0) _DOHASH@f(114,%0)
#define _HASH@f_s(%0) _DOHASH@f(115,%0)
#define _HASH@f_t(%0) _DOHASH@f(116,%0)
#define _HASH@f_u(%0) _DOHASH@f(117,%0)
#define _HASH@f_v(%0) _DOHASH@f(118,%0)
#define _HASH@f_w(%0) _DOHASH@f(119,%0)
#define _HASH@f_x(%0) _DOHASH@f(120,%0)
#define _HASH@f_y(%0) _DOHASH@f(121,%0)
#define _HASH@f_z(%0) _DOHASH@f(122,%0)

// String end.
#define _HASH@f_@(%0) 2166136261

// ============
//  FNV1a hash 
// ============

// Signify the end with two "@" symbols.
#define HASH@fnv1a(%0) _REHASH@a(%0,@,@)

// Internal call.
#define _REHASH@a(%0,%1) _HASH@a_%0(%1)

// The bit that actually does the work.
#define _DOHASH@a(%0,%1,%2) ((_HASH@a_%1(%2)^%0)*16777619)

// Space.
#define _HASH@a_(%0) _DOHASH@a(32,%0)

// Numbers.
#define _HASH@a_0(%0) _DOHASH@a(48,%0)
#define _HASH@a_1(%0) _DOHASH@a(49,%0)
#define _HASH@a_2(%0) _DOHASH@a(50,%0)
#define _HASH@a_3(%0) _DOHASH@a(51,%0)
#define _HASH@a_4(%0) _DOHASH@a(52,%0)
#define _HASH@a_5(%0) _DOHASH@a(53,%0)
#define _HASH@a_6(%0) _DOHASH@a(54,%0)
#define _HASH@a_7(%0) _DOHASH@a(55,%0)
#define _HASH@a_8(%0) _DOHASH@a(56,%0)
#define _HASH@a_9(%0) _DOHASH@a(57,%0)

// Upper case letters.
#define _HASH@a_A(%0) _DOHASH@a(65,%0)
#define _HASH@a_B(%0) _DOHASH@a(66,%0)
#define _HASH@a_C(%0) _DOHASH@a(67,%0)
#define _HASH@a_D(%0) _DOHASH@a(68,%0)
#define _HASH@a_E(%0) _DOHASH@a(69,%0)
#define _HASH@a_F(%0) _DOHASH@a(70,%0)
#define _HASH@a_G(%0) _DOHASH@a(71,%0)
#define _HASH@a_H(%0) _DOHASH@a(72,%0)
#define _HASH@a_I(%0) _DOHASH@a(73,%0)
#define _HASH@a_J(%0) _DOHASH@a(74,%0)
#define _HASH@a_K(%0) _DOHASH@a(75,%0)
#define _HASH@a_L(%0) _DOHASH@a(76,%0)
#define _HASH@a_M(%0) _DOHASH@a(77,%0)
#define _HASH@a_N(%0) _DOHASH@a(78,%0)
#define _HASH@a_O(%0) _DOHASH@a(79,%0)
#define _HASH@a_P(%0) _DOHASH@a(80,%0)
#define _HASH@a_Q(%0) _DOHASH@a(81,%0)
#define _HASH@a_R(%0) _DOHASH@a(82,%0)
#define _HASH@a_S(%0) _DOHASH@a(83,%0)
#define _HASH@a_T(%0) _DOHASH@a(84,%0)
#define _HASH@a_U(%0) _DOHASH@a(85,%0)
#define _HASH@a_V(%0) _DOHASH@a(86,%0)
#define _HASH@a_W(%0) _DOHASH@a(87,%0)
#define _HASH@a_X(%0) _DOHASH@a(88,%0)
#define _HASH@a_Y(%0) _DOHASH@a(89,%0)
#define _HASH@a_Z(%0) _DOHASH@a(90,%0)

// Underscore.
#define _HASH@a__(%0) _DOHASH@a(95,%0)

// Lower case letters.
#define _HASH@a_a(%0) _DOHASH@a(97,%0)
#define _HASH@a_b(%0) _DOHASH@a(98,%0)
#define _HASH@a_c(%0) _DOHASH@a(99,%0)
#define _HASH@a_d(%0) _DOHASH@a(100,%0)
#define _HASH@a_e(%0) _DOHASH@a(101,%0)
#define _HASH@a_f(%0) _DOHASH@a(102,%0)
#define _HASH@a_g(%0) _DOHASH@a(103,%0)
#define _HASH@a_h(%0) _DOHASH@a(104,%0)
#define _HASH@a_i(%0) _DOHASH@a(105,%0)
#define _HASH@a_j(%0) _DOHASH@a(106,%0)
#define _HASH@a_k(%0) _DOHASH@a(107,%0)
#define _HASH@a_l(%0) _DOHASH@a(108,%0)
#define _HASH@a_m(%0) _DOHASH@a(109,%0)
#define _HASH@a_n(%0) _DOHASH@a(110,%0)
#define _HASH@a_o(%0) _DOHASH@a(111,%0)
#define _HASH@a_p(%0) _DOHASH@a(112,%0)
#define _HASH@a_q(%0) _DOHASH@a(113,%0)
#define _HASH@a_r(%0) _DOHASH@a(114,%0)
#define _HASH@a_s(%0) _DOHASH@a(115,%0)
#define _HASH@a_t(%0) _DOHASH@a(116,%0)
#define _HASH@a_u(%0) _DOHASH@a(117,%0)
#define _HASH@a_v(%0) _DOHASH@a(118,%0)
#define _HASH@a_w(%0) _DOHASH@a(119,%0)
#define _HASH@a_x(%0) _DOHASH@a(120,%0)
#define _HASH@a_y(%0) _DOHASH@a(121,%0)
#define _HASH@a_z(%0) _DOHASH@a(122,%0)

// String end.
#define _HASH@a_@(%0) 2166136261

// ==================
//  Case insensitive 
// ==================

// These are the default values
//#define HASHi(%0,%1) HASHi@%0(%1)

//#define _I(%0) _REHASib(%0,@,@)

/*#define _I@b HASHi@bernstein
#define _I@f HASHi@fnv1
#define _I@a HASHi@fnv1a*/

// ================
//  Bernstein hash 
// ================

// Signify the end with two "@" symbols.
#define HASHi@bernstein(%0) _REHASH@ib(%0,@,@)

// Internal call.
#define _REHASH@ib(%0,%1) _HASH@ib_%0(%1)

// The bit that actually does the work.
#define _DOHASH@ib(%0,%1,%2) (_HASH@ib_%1(%2)*33+%0)

// Space.
#define _HASH@ib_(%0) _DOHASH@ib(32,%0)

// Numbers.
#define _HASH@ib_0(%0) _DOHASH@ib(48,%0)
#define _HASH@ib_1(%0) _DOHASH@ib(49,%0)
#define _HASH@ib_2(%0) _DOHASH@ib(50,%0)
#define _HASH@ib_3(%0) _DOHASH@ib(51,%0)
#define _HASH@ib_4(%0) _DOHASH@ib(52,%0)
#define _HASH@ib_5(%0) _DOHASH@ib(53,%0)
#define _HASH@ib_6(%0) _DOHASH@ib(54,%0)
#define _HASH@ib_7(%0) _DOHASH@ib(55,%0)
#define _HASH@ib_8(%0) _DOHASH@ib(56,%0)
#define _HASH@ib_9(%0) _DOHASH@ib(57,%0)

// Upper case letters.
#define _HASH@ib_A(%0) _DOHASH@ib(65,%0)
#define _HASH@ib_B(%0) _DOHASH@ib(66,%0)
#define _HASH@ib_C(%0) _DOHASH@ib(67,%0)
#define _HASH@ib_D(%0) _DOHASH@ib(68,%0)
#define _HASH@ib_E(%0) _DOHASH@ib(69,%0)
#define _HASH@ib_F(%0) _DOHASH@ib(70,%0)
#define _HASH@ib_G(%0) _DOHASH@ib(71,%0)
#define _HASH@ib_H(%0) _DOHASH@ib(72,%0)
#define _HASH@ib_I(%0) _DOHASH@ib(73,%0)
#define _HASH@ib_J(%0) _DOHASH@ib(74,%0)
#define _HASH@ib_K(%0) _DOHASH@ib(75,%0)
#define _HASH@ib_L(%0) _DOHASH@ib(76,%0)
#define _HASH@ib_M(%0) _DOHASH@ib(77,%0)
#define _HASH@ib_N(%0) _DOHASH@ib(78,%0)
#define _HASH@ib_O(%0) _DOHASH@ib(79,%0)
#define _HASH@ib_P(%0) _DOHASH@ib(80,%0)
#define _HASH@ib_Q(%0) _DOHASH@ib(81,%0)
#define _HASH@ib_R(%0) _DOHASH@ib(82,%0)
#define _HASH@ib_S(%0) _DOHASH@ib(83,%0)
#define _HASH@ib_T(%0) _DOHASH@ib(84,%0)
#define _HASH@ib_U(%0) _DOHASH@ib(85,%0)
#define _HASH@ib_V(%0) _DOHASH@ib(86,%0)
#define _HASH@ib_W(%0) _DOHASH@ib(87,%0)
#define _HASH@ib_X(%0) _DOHASH@ib(88,%0)
#define _HASH@ib_Y(%0) _DOHASH@ib(89,%0)
#define _HASH@ib_Z(%0) _DOHASH@ib(90,%0)

// Underscore.
#define _HASH@ib__(%0) _DOHASH@ib(95,%0)

// Lower case letters.
#define _HASH@ib_a(%0) _DOHASH@ib(65,%0)
#define _HASH@ib_b(%0) _DOHASH@ib(66,%0)
#define _HASH@ib_c(%0) _DOHASH@ib(67,%0)
#define _HASH@ib_d(%0) _DOHASH@ib(68,%0)
#define _HASH@ib_e(%0) _DOHASH@ib(69,%0)
#define _HASH@ib_f(%0) _DOHASH@ib(70,%0)
#define _HASH@ib_g(%0) _DOHASH@ib(71,%0)
#define _HASH@ib_h(%0) _DOHASH@ib(72,%0)
#define _HASH@ib_i(%0) _DOHASH@ib(73,%0)
#define _HASH@ib_j(%0) _DOHASH@ib(74,%0)
#define _HASH@ib_k(%0) _DOHASH@ib(75,%0)
#define _HASH@ib_l(%0) _DOHASH@ib(76,%0)
#define _HASH@ib_m(%0) _DOHASH@ib(77,%0)
#define _HASH@ib_n(%0) _DOHASH@ib(78,%0)
#define _HASH@ib_o(%0) _DOHASH@ib(79,%0)
#define _HASH@ib_p(%0) _DOHASH@ib(80,%0)
#define _HASH@ib_q(%0) _DOHASH@ib(81,%0)
#define _HASH@ib_r(%0) _DOHASH@ib(82,%0)
#define _HASH@ib_s(%0) _DOHASH@ib(83,%0)
#define _HASH@ib_t(%0) _DOHASH@ib(84,%0)
#define _HASH@ib_u(%0) _DOHASH@ib(85,%0)
#define _HASH@ib_v(%0) _DOHASH@ib(86,%0)
#define _HASH@ib_w(%0) _DOHASH@ib(87,%0)
#define _HASH@ib_x(%0) _DOHASH@ib(88,%0)
#define _HASH@ib_y(%0) _DOHASH@ib(89,%0)
#define _HASH@ib_z(%0) _DOHASH@ib(90,%0)

// String end.
#define _HASH@ib_@(%0) -1

// ===========
//  FNV1 hash 
// ===========

// Signify the end with two "@" symbols.
#define HASHi@fnv1(%0) _REHASH@if(%0,@,@)

// Internal call.
#define _REHASH@if(%0,%1) _HASH@if_%0(%1)

// The bit that actually does the work.
#define _DOHASH@if(%0,%1,%2) (_HASH@if_%1(%2)*16777619^%0)

// Space.
#define _HASH@if_(%0) _DOHASH@if(32,%0)

// Numbers.
#define _HASH@if_0(%0) _DOHASH@if(48,%0)
#define _HASH@if_1(%0) _DOHASH@if(49,%0)
#define _HASH@if_2(%0) _DOHASH@if(50,%0)
#define _HASH@if_3(%0) _DOHASH@if(51,%0)
#define _HASH@if_4(%0) _DOHASH@if(52,%0)
#define _HASH@if_5(%0) _DOHASH@if(53,%0)
#define _HASH@if_6(%0) _DOHASH@if(54,%0)
#define _HASH@if_7(%0) _DOHASH@if(55,%0)
#define _HASH@if_8(%0) _DOHASH@if(56,%0)
#define _HASH@if_9(%0) _DOHASH@if(57,%0)

// Upper case letters.
#define _HASH@if_A(%0) _DOHASH@if(65,%0)
#define _HASH@if_B(%0) _DOHASH@if(66,%0)
#define _HASH@if_C(%0) _DOHASH@if(67,%0)
#define _HASH@if_D(%0) _DOHASH@if(68,%0)
#define _HASH@if_E(%0) _DOHASH@if(69,%0)
#define _HASH@if_F(%0) _DOHASH@if(70,%0)
#define _HASH@if_G(%0) _DOHASH@if(71,%0)
#define _HASH@if_H(%0) _DOHASH@if(72,%0)
#define _HASH@if_I(%0) _DOHASH@if(73,%0)
#define _HASH@if_J(%0) _DOHASH@if(74,%0)
#define _HASH@if_K(%0) _DOHASH@if(75,%0)
#define _HASH@if_L(%0) _DOHASH@if(76,%0)
#define _HASH@if_M(%0) _DOHASH@if(77,%0)
#define _HASH@if_N(%0) _DOHASH@if(78,%0)
#define _HASH@if_O(%0) _DOHASH@if(79,%0)
#define _HASH@if_P(%0) _DOHASH@if(80,%0)
#define _HASH@if_Q(%0) _DOHASH@if(81,%0)
#define _HASH@if_R(%0) _DOHASH@if(82,%0)
#define _HASH@if_S(%0) _DOHASH@if(83,%0)
#define _HASH@if_T(%0) _DOHASH@if(84,%0)
#define _HASH@if_U(%0) _DOHASH@if(85,%0)
#define _HASH@if_V(%0) _DOHASH@if(86,%0)
#define _HASH@if_W(%0) _DOHASH@if(87,%0)
#define _HASH@if_X(%0) _DOHASH@if(88,%0)
#define _HASH@if_Y(%0) _DOHASH@if(89,%0)
#define _HASH@if_Z(%0) _DOHASH@if(90,%0)

// Underscore.
#define _HASH@if__(%0) _DOHASH@if(95,%0)

// Lower case letters.
#define _HASH@if_a(%0) _DOHASH@if(65,%0)
#define _HASH@if_b(%0) _DOHASH@if(66,%0)
#define _HASH@if_c(%0) _DOHASH@if(67,%0)
#define _HASH@if_d(%0) _DOHASH@if(68,%0)
#define _HASH@if_e(%0) _DOHASH@if(69,%0)
#define _HASH@if_f(%0) _DOHASH@if(70,%0)
#define _HASH@if_g(%0) _DOHASH@if(71,%0)
#define _HASH@if_h(%0) _DOHASH@if(72,%0)
#define _HASH@if_i(%0) _DOHASH@if(73,%0)
#define _HASH@if_j(%0) _DOHASH@if(74,%0)
#define _HASH@if_k(%0) _DOHASH@if(75,%0)
#define _HASH@if_l(%0) _DOHASH@if(76,%0)
#define _HASH@if_m(%0) _DOHASH@if(77,%0)
#define _HASH@if_n(%0) _DOHASH@if(78,%0)
#define _HASH@if_o(%0) _DOHASH@if(79,%0)
#define _HASH@if_p(%0) _DOHASH@if(80,%0)
#define _HASH@if_q(%0) _DOHASH@if(81,%0)
#define _HASH@if_r(%0) _DOHASH@if(82,%0)
#define _HASH@if_s(%0) _DOHASH@if(83,%0)
#define _HASH@if_t(%0) _DOHASH@if(84,%0)
#define _HASH@if_u(%0) _DOHASH@if(85,%0)
#define _HASH@if_v(%0) _DOHASH@if(86,%0)
#define _HASH@if_w(%0) _DOHASH@if(87,%0)
#define _HASH@if_x(%0) _DOHASH@if(88,%0)
#define _HASH@if_y(%0) _DOHASH@if(89,%0)
#define _HASH@if_z(%0) _DOHASH@if(90,%0)

// String end.
#define _HASH@if_@(%0) 2166136261

// ============
//  FNV1a hash 
// ============

// Signify the end with two "@" symbols.
#define HASHi@fnv1a(%0) _REHASH@ia(%0,@,@)

// Internal call.
#define _REHASH@ia(%0,%1) _HASH@ia_%0(%1)

// The bit that actually does the work.
#define _DOHASH@ia(%0,%1,%2) ((_HASH@ia_%1(%2)^%0)*16777619)

// Space.
#define _HASH@ia_(%0) _DOHASH@ia(32,%0)

// Numbers.
#define _HASH@ia_0(%0) _DOHASH@ia(48,%0)
#define _HASH@ia_1(%0) _DOHASH@ia(49,%0)
#define _HASH@ia_2(%0) _DOHASH@ia(50,%0)
#define _HASH@ia_3(%0) _DOHASH@ia(51,%0)
#define _HASH@ia_4(%0) _DOHASH@ia(52,%0)
#define _HASH@ia_5(%0) _DOHASH@ia(53,%0)
#define _HASH@ia_6(%0) _DOHASH@ia(54,%0)
#define _HASH@ia_7(%0) _DOHASH@ia(55,%0)
#define _HASH@ia_8(%0) _DOHASH@ia(56,%0)
#define _HASH@ia_9(%0) _DOHASH@ia(57,%0)

// Upper case letters.
#define _HASH@ia_A(%0) _DOHASH@ia(65,%0)
#define _HASH@ia_B(%0) _DOHASH@ia(66,%0)
#define _HASH@ia_C(%0) _DOHASH@ia(67,%0)
#define _HASH@ia_D(%0) _DOHASH@ia(68,%0)
#define _HASH@ia_E(%0) _DOHASH@ia(69,%0)
#define _HASH@ia_F(%0) _DOHASH@ia(70,%0)
#define _HASH@ia_G(%0) _DOHASH@ia(71,%0)
#define _HASH@ia_H(%0) _DOHASH@ia(72,%0)
#define _HASH@ia_I(%0) _DOHASH@ia(73,%0)
#define _HASH@ia_J(%0) _DOHASH@ia(74,%0)
#define _HASH@ia_K(%0) _DOHASH@ia(75,%0)
#define _HASH@ia_L(%0) _DOHASH@ia(76,%0)
#define _HASH@ia_M(%0) _DOHASH@ia(77,%0)
#define _HASH@ia_N(%0) _DOHASH@ia(78,%0)
#define _HASH@ia_O(%0) _DOHASH@ia(79,%0)
#define _HASH@ia_P(%0) _DOHASH@ia(80,%0)
#define _HASH@ia_Q(%0) _DOHASH@ia(81,%0)
#define _HASH@ia_R(%0) _DOHASH@ia(82,%0)
#define _HASH@ia_S(%0) _DOHASH@ia(83,%0)
#define _HASH@ia_T(%0) _DOHASH@ia(84,%0)
#define _HASH@ia_U(%0) _DOHASH@ia(85,%0)
#define _HASH@ia_V(%0) _DOHASH@ia(86,%0)
#define _HASH@ia_W(%0) _DOHASH@ia(87,%0)
#define _HASH@ia_X(%0) _DOHASH@ia(88,%0)
#define _HASH@ia_Y(%0) _DOHASH@ia(89,%0)
#define _HASH@ia_Z(%0) _DOHASH@ia(90,%0)

// Underscore.
#define _HASH@ia__(%0) _DOHASH@ia(95,%0)

// Lower case letters.
#define _HASH@ia_a(%0) _DOHASH@ia(65,%0)
#define _HASH@ia_b(%0) _DOHASH@ia(66,%0)
#define _HASH@ia_c(%0) _DOHASH@ia(67,%0)
#define _HASH@ia_d(%0) _DOHASH@ia(68,%0)
#define _HASH@ia_e(%0) _DOHASH@ia(69,%0)
#define _HASH@ia_f(%0) _DOHASH@ia(70,%0)
#define _HASH@ia_g(%0) _DOHASH@ia(71,%0)
#define _HASH@ia_h(%0) _DOHASH@ia(72,%0)
#define _HASH@ia_i(%0) _DOHASH@ia(73,%0)
#define _HASH@ia_j(%0) _DOHASH@ia(74,%0)
#define _HASH@ia_k(%0) _DOHASH@ia(75,%0)
#define _HASH@ia_l(%0) _DOHASH@ia(76,%0)
#define _HASH@ia_m(%0) _DOHASH@ia(77,%0)
#define _HASH@ia_n(%0) _DOHASH@ia(78,%0)
#define _HASH@ia_o(%0) _DOHASH@ia(79,%0)
#define _HASH@ia_p(%0) _DOHASH@ia(80,%0)
#define _HASH@ia_q(%0) _DOHASH@ia(81,%0)
#define _HASH@ia_r(%0) _DOHASH@ia(82,%0)
#define _HASH@ia_s(%0) _DOHASH@ia(83,%0)
#define _HASH@ia_t(%0) _DOHASH@ia(84,%0)
#define _HASH@ia_u(%0) _DOHASH@ia(85,%0)
#define _HASH@ia_v(%0) _DOHASH@ia(86,%0)
#define _HASH@ia_w(%0) _DOHASH@ia(87,%0)
#define _HASH@ia_x(%0) _DOHASH@ia(88,%0)
#define _HASH@ia_y(%0) _DOHASH@ia(89,%0)
#define _HASH@ia_z(%0) _DOHASH@ia(90,%0)

// String end.
#define _HASH@ia_@(%0) 2166136261

// ============
//  Other code 
// ============

enum e_HASH_TYPE
{
	hash_bernstein,
	hash_fnv1,
	hash_fnv1a
}

/*----------------------------------------------------------------------------*-
Function:
	Hash
Params:
	str - The string to hash.
	sensitive - Wether the hash is case sensitive or not.
Return:
	The reverse Bernstein hash of the string.
Notes:
	Based on Bernstein hash, but backwards to match the macros.  The only
	characters which can be used in the compile time version of this code are:
	a-z, A-Z, 0-9, _ and space.

native Hash(str[]);

-*----------------------------------------------------------------------------*/

stock YHash(const str[], bool:sensitive = true, e_HASH_TYPE:type = hash_bernstein, len = -1)
{
	if (len == -1)
	{
		len = strlen(str);
	}
	switch (type)
	{
		case hash_bernstein:
		{
			new
				hash = -1;
			if (sensitive)
			{
				while (len--)
				{
					hash = hash * 33 + str[len];
				}
			}
			else
			{
				while (len--)
				{
					new
						ch = str[len];
					if ('a' <= ch <= 'z')
					{
						ch &= ~0x20;
					}
					hash = hash * 33 + ch;
				}
			}
			return hash;
		}
		case hash_fnv1:
		{
			new
				hash = 2166136261;
			if (sensitive)
			{
				while (len--)
				{
					hash = hash * 16777619 ^ str[len];
				}
			}
			else
			{
				while (len--)
				{
					new
						ch = str[len];
					if ('a' <= ch <= 'z')
					{
						ch &= ~0x20;
					}
					hash = hash * 16777619 ^ ch;
				}
			}
			return hash;
		}
		case hash_fnv1a:
		{
			new
				hash = 2166136261;
			if (sensitive)
			{
				while (len--)
				{
					hash = (hash ^ str[len]) * 16777619;
				}
			}
			else
			{
				while (len--)
				{
					new
						ch = str[len];
					if ('a' <= ch <= 'z')
					{
						ch &= ~0x20;
					}
					hash = (hash ^ ch) * 16777619;
				}
			}
			return hash;
		}
	}
	return -1;
}
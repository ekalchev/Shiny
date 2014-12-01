///////////////////////////////////////////////////////////////////////////////
//	File:    MailboxPrim.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __MAILBOXPRIM__
#define __MAILBOXPRIM__

template<class Primitive>
struct MailboxPrim
{
	const Primitive* primitive;
	int lastMailboxId;

	MailboxPrim(const Primitive* p)
	{
		primitive = p;
		lastMailboxId = -1;
	}
};
#endif
#include <prodcons.h>
int n;  
shellcmd xsh_prodcons(int nargs, char *args[]) 
{       
  //Argument verifications and validations         

  int count = 2000;  //local varible to hold count  
  if(args[1] is present ])  
  {											
    count	= args[1];							
  }														
  //create	the	process	produer	and	consumer	and	put	them	in	ready	queue.
  //Look	at	the	definations	of	function	create	and	resume	in	exinu/system	
  //folder	for	
  // reference.													
  resume(	create(producer,	1024,	20,	"producer",	1,	count)	);							
  resume(	create(consumer,	1024,	20,	"consumer",	1,	count)	);															
}	
}

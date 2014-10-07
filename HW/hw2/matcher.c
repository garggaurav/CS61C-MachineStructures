/**
 * The contents of this file are only a suggestion.
 * Feel free to change anything.
 */

#include "matcher.h"

/**
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */

int matches_leading(char *partial_line, char *pattern) 
{
  // You can use this recommended helper function, or not.
  	if(pattern[0] == '\0')
		  return 1;
	  if(partial_line[0] == '\0' && pattern[1]!='?' && pattern[0]!='\\') 
		  return 0;

    if(pattern[0]=='\\')
    {
      if(partial_line[0]=='\0' || pattern[2]=='?')
        return matches_leading(partial_line, pattern+1);
    	if(pattern[1]==partial_line[0]) //check if the following characters match
    		return matches_leading(partial_line+1, pattern+2);
    	else
    		return 0;
    }

   	if(pattern[1]=='?')
   	{
      if(partial_line[0]=='\0')
          return matches_leading(partial_line, pattern+2);

      if(pattern[0]=='.')
          return (matches_leading(partial_line+1, pattern+2) || matches_leading(partial_line, pattern+2));

   		if(pattern[0]!=pattern[2] && pattern[0]==partial_line[0])
   			return matches_leading(partial_line+1, pattern+2) || matches_leading(partial_line, pattern+2);
      else
        return matches_leading(partial_line, pattern+2);
   	}

   	if(pattern[0]=='.' && pattern[1]=='+')
   	{
   		while(partial_line[0]!='\0')
   		{
        partial_line+=1;
   			if(matches_leading(partial_line, pattern+2)==1)
   				return 1;
   		}
   		return 0;
   	}

    if(pattern[0]=='+')
    {
      char* spec = &*pattern - 1; //get the char before +
      while(partial_line[0]!='\0')
      {
        if(partial_line[0] != *spec)
          return matches_leading(partial_line, pattern+1);
        if(matches_leading(partial_line, pattern+1)==1)
          return 1;
        partial_line+=1;
      }
      return 0;
    }

	if(pattern[0] == partial_line[0] || pattern[0] == '.')
	{
		return matches_leading(partial_line+1, pattern+1); 
  }
   	
    return 0;
}

/**
 * Implementation of your matcher function, which
 * will be called by the main program.
 *
 * You may assume that both line and pattern point
 * to reasonably short, null-terminated strings.
 */
int rgrep_matches(char *line, char *pattern) 
{
	while(*line)
	{
		if(matches_leading(line, pattern))
			return 1;
		else
		{
			line+=1;
			matches_leading(line, pattern);
		}
	}
	return 0;
}


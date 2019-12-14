//Sukhveer Karlcut
//ID: 1704725
//cruzID: skarlcut
//pa1

import java.io.*;
import java.util.*;

class Lex
{
	public static void main (String[] args) throws IOException{
		Scanner in = null;
 		PrintWriter out = null;
	 	String line = null;
	 	String[] token = null;
	 	int lineNumber = 0; 
		int n = 0;
		//check if correct number of args was entered
	 	if(args.length < 2 || args.length > 2 || args[0] == null || args[1] == null){
	 		System.err.println("Usage: Lex infile outfile");
	 	   	System.exit(1);
	 	}
	 	     
	 	in = new Scanner(new File(args[0]));
	 	out = new PrintWriter(new FileWriter(args[1]));
		//count number of lines and read input	
		while( in.hasNextLine() )
		{
			lineNumber++;
			in.nextLine();
		}
		in = new Scanner(new File(args[0]));
		token = new String[lineNumber];
		while( in.hasNextLine() )
		{
			token[n] = in.nextLine();
			n++;
		}
		//create list and insert lines alphabetically using insertion sort
		List l = new List();
		l.append(0);
		for(int i = 1; i < token.length; i ++)
		{
			l.moveFront();
	        	while(l.index() >= 0 && (token[i]).compareTo(token[l.get()]) > 0)
	        	        l.moveNext();
			if(l.index() != -1)
	        		l.insertBefore(i);
			else
				l.append(i);
		}
		//write to output file
		for(l.moveFront(); l.index() >= 0; l.moveNext())
			out.println(token[l.get()]);
		in.close();
		out.close();
	}
}

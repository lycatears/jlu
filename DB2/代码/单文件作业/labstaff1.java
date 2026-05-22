import java.sql.*;
import java.io.*;
import java.util.*;
import java.math.*;
public class labstaff1 
{
 static
    {   try { 
              /******************* ??????????????? *****************/
              /* ( 1 ) Load the DB2 Driver                         */
              /*****************************************************/
              Class.forName ("COM.ibm.db2.jdbc.app.DB2Driver"); // (1)
        }
        catch (Exception e)
        {   System.exit(1);  }
    }

  public static void main( String args[]) throws Exception
  {
   int mydeptno = 0;
   String deptno = "";
   String outline = " ";
   String name = " ";
   String job = " ";
   String salary = "";
   /***********************************************************************/
   /* Header line                                                         */
   /***********************************************************************/
   String  intext =
   "\n ID       NAME      SALARY\n";
   String  indash =
   "--------  --------  --------------\n";
   String blanks = "                                                        ";


   /********************** ???????????????????? ***************************/
   /* ( 2 ) Define the variable SQLWarn that is used for SQLWarnings      */
   /***********************************************************************/
   SQLWarning     SQLWarn = null;  

   /********************** ???????????????????? ****************************/
   /* ( 3 ) Connect to the DB2 Database SAMPLE.                            */
   /************************************************************************/

   Connection sample = DriverManager.getConnection("jdbc:db2:sample","JLU","826132");   
   System.out.println("\n Set AutoCommit off");
   sample.setAutoCommit( false);
   System.out.println("\n Autocommit off");
   try 
   {  
      System.out.println("\n Enter the Department number\n");
      BufferedReader in = new BufferedReader( new InputStreamReader (System.in));
      String s;
      s = in.readLine();
      deptno = s.substring(0,2);
      mydeptno = Integer.parseInt(deptno);
     
    }  // End try
   catch (Exception e) {e.printStackTrace(); System.exit(0);}
   try 
     { 
       
       /******************* ??????????????????????? *************************/
       /* ( 4 ) Instantiate the PreparedStatement object name stmt.         */
       /*       Use the prepareStatement() method.                          */
       /*********************************************************************/
       PreparedStatement stmt = sample.prepareStatement(
           "select id, name,salary from staff where Dept = ?");    
       /******************* ??????????????????????? *************************/
       /* ( 5 ) Set the parameter in the PreparedStatement object stmt to   */
       /*       the variable name mydeptno.                                 */
       /*********************************************************************/
       stmt.setInt(1, mydeptno);
       /******************* ??????????????????????? *************************/
       /* ( 6 ) Declare the ResultSet object rs and assign the results      */
       /*       of the SQL select statement.                                */
       /*********************************************************************/
       ResultSet rs = stmt.executeQuery();
       /************************* ??????????????? ************************/
       /* ( 7 ) If SQLWarning occurs display the warning                 */
       /******************************************************************/
       if ( (SQLWarn = stmt.getWarnings()) != null )
        {
          System.out.println ("\n Value of SQLWarn on single row insert to DEP is: \n");
          System.out.println (SQLWarn);
        } // end if
       /************************* ???????????????? ***********************/
       /* ( 8 ) Use the ResultSet next() method to retrieve the first    */
       /*       row of the ResultSet.                                    */
       /******************************************************************/
       boolean more = rs.next();
       System.out.println ( intext );
       System.out.println ( indash );                                  
      
       while ( more ) {
            name = rs.getString(1);
            job = rs.getString(2);
            salary = rs.getString(3);
            outline = (name + blanks.substring(0, 10 - name.length())) +
                             (job + blanks.substring(0, 10 - job.length()))   +
                             (salary + blanks.substring(0, 12 - salary.length()));
            System.out.println("\n" + outline);
            /******************* ????????????????????? ********************/
            /* ( 9 ) Retrieve the next row of the Result Set              */
            /**************************************************************/
            more = rs.next();
                       }
     }
     catch (Exception e)
        {  System.exit(1); }
   }
} 
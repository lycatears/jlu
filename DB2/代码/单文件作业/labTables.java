/**********************************************************************/
/* labTables.java                                                     */
/*                                                                    */
/* Sample Java program for "DB2 UDB PROGRAMMING USING JAVA"           */
/*                          ( CG11 )                                  */
/*                                                                    */
/*                                                                    */
/* Last update = 01/01/2003                                           */
/*                                                                    */
/**********************************************************************/
/*  Notes:                                                            */
/*                                                                    */
/*  This program is intended to be completed with the lab guide       */
/*  as a reference.  The lab guide is the set of instructions that    */
/*  should be followed.  The comments in this program are intended    */
/*  to clarify statements made in the lab guide.                      */
/*  This program will demonstrate how to use metadata methods.        */
/**********************************************************************/

/**********************??????????????? ***********************/
/* (1) Code the import statement to include the classes and  */
/*     interfaces for SQL                                    */
/*************************************************************/
import java.sql.*;

import java.io.*;
import java.util.*;
import java.math.*;
public class labTables
{
 static
    {   try
        {   
           /********************* ???????????? ***************/
           /* (2) Load the DB2Driver                         */
           /**************************************************/
           Class.forName ("COM.ibm.db2.jdbc.app.DB2Driver");  
        }
        catch (Exception e)
        {   System.exit(1);
        }
    }
  public static void main( String args[]) throws Exception
  {
   try {
   
   /***************************** ?????????????????? *****************/
   /* (3) Code the statement to connect to the DB2 database named    */
   /*     SAMPLE.  Use the Connection object named sample.           */
   /******************************************************************/   
   Connection sample = DriverManager.getConnection("jdbc:db2:sample");    
   
   /******************* ?????????????????????? ***********************/
   /* ( 4 ) Create the DatabaseMetaData object named dbmd.           */
   /*                                                                */
   /******************************************************************/
   DatabaseMetaData dbmd = sample.getMetaData();

   /******************* ?????????????????????? ***********************/
   /* ( 5 ) Define the String array tableTypes so that the metadata  */
   /*       method getTables will return tables and views            */
   /******************************************************************/
   String [] tableTypes = {"TABLE", "VIEW"};

   /******************* ?????????????????????? ***********************/
   /* ( 6 ) Define the ResultSet rs to get the description of the    */
   /*       tables for the schema UDBA.  Use the DatabaseMetaData    */
   /*       object named dbmd created in step 4.                     */
   /*       Use the getTables( ) method                              */
   /******************************************************************/
   
   ResultSet rs = dbmd.getTables(null, "JLU", "%",tableTypes);

   while (rs.next()) {
        String s = rs.getString(1);
        System.out.println("\nCatalog Name: " + s + " Schema Name: " + rs.getString(2) + 
             " Table Name: " + rs.getString(3) );
       }
   }  // End try
   catch (Exception e)
        { System.out.println ("\n Error MetaData Call");
          System.out.println ("\n " + e); 
          System.exit(1);
        }
   }
} 
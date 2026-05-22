import java.sql.*;

public class ClobExer {
	static
    {   try
        {   Class.forName ("COM.ibm.db2.jdbc.app.DB2Driver");
        }
        catch (Exception e)
        {   System.out.println ("\n  Error loading DB2 Driver...\n");
            System.out.println (e);
            System.exit(1);
        }
    }
    public static void main(String[] args) {
        try {
            String resume = null;
            String empnum = "000130";
            int startper = 0, startper1 = 0, startdpt = 0;
            PreparedStatement stmt1, stmt2, stmt3 = null;
            String sql1, sql2, sql3 = null;
            String empno, resumefmt = null;
            Clob resumelob = null;
            ResultSet rs1, rs2, rs3 = null;
            Connection conn = DriverManager.getConnection("jdbc:db2:sample", "JLU", "826132");
            sql1 = "SELECT POSSTR(RESUME,'Personal') "
                    + "FROM EMP_RESUME "
                    + "WHERE EMPNO = ? AND RESUME_FORMAT = 'ascii' ";
            stmt1 = conn.prepareStatement(sql1);
            stmt1.setString(1, empnum);
            rs1 = stmt1.executeQuery();
            while (rs1.next()) {
                startper = rs1.getInt(1);
            } // end while

            sql2 = "SELECT POSSTR(RESUME,'Department') "
                    + "FROM EMP_RESUME "
                    + "WHERE EMPNO = ? AND RESUME_FORMAT = 'ascii' ";
            stmt2 = conn.prepareStatement(sql2);
            stmt2.setString(1, empnum);
            rs2 = stmt2.executeQuery();
            while (rs2.next()) {
                startdpt = rs2.getInt(1);
            } // end while

            startper1 = startper - 1;
            sql3 = "SELECT EMPNO, RESUME_FORMAT, "
                    + "SUBSTR(RESUME,1,?)|| SUBSTR(RESUME,?) AS RESUME "
                    + "FROM EMP_RESUME "
                    + "WHERE EMPNO = ? AND RESUME_FORMAT = 'ascii' ";
            stmt3 = conn.prepareStatement(sql3);
            stmt3.setInt(1, startper1);
            stmt3.setInt(2, startdpt);
            stmt3.setString(3, empnum);
            rs3 = stmt3.executeQuery();
            while (rs3.next()) {
                empno = rs3.getString(1);
                resumefmt = rs3.getString(2);
                resumelob = rs3.getClob(3);
                long len = resumelob.length();
                int len1 = (int) len;
                String resumeout = resumelob.getSubString(1, len1);
                System.out.println(resumeout);
            } // end while
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}

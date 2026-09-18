package org.example.booksys.utils;

import org.apache.ibatis.type.JdbcType;
import org.apache.ibatis.type.MappedJdbcTypes;
import org.apache.ibatis.type.MappedTypes;
import org.apache.ibatis.type.TypeHandler;

import java.sql.*;

@MappedJdbcTypes(JdbcType.BLOB)
@MappedTypes(byte[].class)
public class BlobTypeHandler implements TypeHandler<byte[]> {
    @Override
    public void setParameter(PreparedStatement ps, int i, byte[] parameter, JdbcType jdbcType) throws SQLException {
        ps.setBytes(i, parameter);
    }

    @Override
    public byte[] getResult(ResultSet rs, String columnName) throws SQLException {
        Blob blob = rs.getBlob(columnName);
        return blob != null ? blob.getBytes(1, (int) blob.length()) : null;
    }

    @Override
    public byte[] getResult(ResultSet rs, int columnIndex) throws SQLException {
        Blob blob = rs.getBlob(columnIndex);
        return blob != null ? blob.getBytes(1, (int) blob.length()) : null;
    }

    @Override
    public byte[] getResult(CallableStatement cs, int columnIndex) throws SQLException {
        Blob blob = cs.getBlob(columnIndex);
        return blob != null ? blob.getBytes(1, (int) blob.length()) : null;
    }
}

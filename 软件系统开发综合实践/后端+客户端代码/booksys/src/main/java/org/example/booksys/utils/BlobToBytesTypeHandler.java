package org.example.booksys.utils;

import org.apache.ibatis.type.BaseTypeHandler;
import org.apache.ibatis.type.JdbcType;

import java.io.InputStream;
import java.sql.*;

public class BlobToBytesTypeHandler extends BaseTypeHandler<byte[]> {

    @Override
    public void setNonNullParameter(PreparedStatement ps, int i, byte[] parameter, JdbcType jdbcType)
            throws SQLException {
        ps.setBytes(i, parameter);
    }

    @Override
    public byte[] getNullableResult(ResultSet rs, String columnName)
            throws SQLException {
        return toBytes(rs.getBlob(columnName));
    }

    @Override
    public byte[] getNullableResult(ResultSet rs, int columnIndex)
            throws SQLException {
        return toBytes(rs.getBlob(columnIndex));
    }

    @Override
    public byte[] getNullableResult(CallableStatement cs, int columnIndex)
            throws SQLException {
        return toBytes(cs.getBlob(columnIndex));
    }

    private byte[] toBytes(Blob blob) throws SQLException {
        if (blob == null) return null;
        try (InputStream is = blob.getBinaryStream()) {
            return is.readAllBytes();
        } catch (Exception e) {
            throw new SQLException("Failed to read BLOB as byte[]", e);
        }
    }
}


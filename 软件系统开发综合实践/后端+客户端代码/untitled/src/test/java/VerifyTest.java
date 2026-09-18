import org.example.Verify;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

public class VerifyTest {
    @DisplayName("加法测试")
    @Test
    public void test() {
        int a = 1;
        int b = 2;
        int c = Verify.fun(a,b);
        Assertions.assertEquals(c,3);
    }
}

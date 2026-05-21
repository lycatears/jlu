@REM Start the server
@REM 不能直接运行 server.server.py是作为包导入的，需要使用uvicorn启动
@REM --reload参数表示自动重启，当 server.py文件修改后，自动重启
uvicorn server:app --reload
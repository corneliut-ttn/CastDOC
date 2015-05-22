
<!-- saved from url=(0056)http://www.htmlgoodies.com/legacy/beyond/asp/engine.html -->
<html><head><meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1"><title>Engine.html</title>




<style type="text/css"></style></head><body style="zoom: 1;" shm_addon_injected="0.9.8.1"><center>
<h3>Save this page as engine.asp</h3>
<b>Copy and paste below this line</b></center>

<p></p><hr width="75%"><p>



<nobr>


&lt;%@ LANGUAGE="VBSCRIPT" %&gt;<br>
<br>
&lt;%<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;' Connects and opens the text file<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;' DATA FORMAT IN TEXT FILE= "username&lt;SPACE&gt;password"<br><br>
	
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Set MyFileObject=Server.CreateObject("Scripting.FileSystemObject")<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Set MyTextFile=MyFileObject.OpenTextFile(Server.MapPath("<b>\path\path\path\path</b>") &amp; "<b>\passwords.txt</b>")
	<br><br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;' Scan the text file to determine if the user is legal<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;WHILE NOT MyTextFile.AtEndOfStream<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	' If username and password found<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	IF MyTextFile.ReadLine = Request.form("username") &amp; " " &amp; Request.form("password") THEN<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;		' Close the text file<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;		MyTextFile.Close<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;		' Go to login success page<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;		Session("GoBack")=Request.ServerVariables("SCRIPT_NAME")<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;		Response.Redirect "<b>inyougo.asp</b>"<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;		Response.end<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	END IF<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;WEND<br>
	<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;' Close the text file<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;MyTextFile.Close<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;' Go to error page if login unsuccessful<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Session("GoBack")=Request.ServerVariables("SCRIPT_NAME")<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Response.Redirect "<b>invalid.asp</b>"<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Response.end<br>
	<br>
%&gt;


</nobr>

</p><p>
</p><p></p><hr width="75%"><p>

<b></b></p><center><b>End Copy and Paste Above the Line</b></center> 



</body></html>
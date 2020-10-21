Public Class Form1

    Dim redist As Boolean = False

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Label1.Visible = False
        Button1.Visible = False
        CheckBox1.Visible = False

        Dim run As Object
        run = CreateObject("Wscript.Shell")
        run.RUN("""" & CurDir() & "\files\setup.bat""", 0, True)

        If redist Then
            run.RUN("""" & CurDir() & "\files\redist.exe""", 0, True)
        End If

    End Sub

    Private Sub CheckBox1_CheckedChanged(sender As Object, e As EventArgs) Handles CheckBox1.CheckedChanged
        redist = Not redist
    End Sub

End Class

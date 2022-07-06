unit UtilsColor;

interface
uses                    
  Windows, Messages, SysUtils, Variants, Classes, Graphics,ComCtrls;
 procedure TextOut(x,y,l:integer;s:string;Canvas:TCanvas);
 procedure AddLineToRichEdit(RichEdit:TRichEdit;s:string);
 function colorToStrR(i:integer):string;
implementation
 procedure TextOut(x,y,l:integer;s:string;Canvas:TCanvas);
  var i:integer;
//      command:char;
      bs:TBrushStyle;
      color:integer;
      scolor:string;
  procedure draw;
   begin
    Canvas.TextOut(x,y,s[i]);
    x:=x+Canvas.TextWidth(s[i]);
   end;
  begin
   i:=1;
   bs:=Canvas.Brush.Style;
   Canvas.Brush.Style:=bsClear;
   try
   while (i<=length(s))and(x<l) do
    begin
      if s[i]<>'<' then
       draw
        else
       if i<length(s) then
       begin
        inc(i);
        case s[i] of
         'I':begin Canvas.Font.Style:=Canvas.Font.Style+[fsItalic];inc(i); end;
         'i':begin Canvas.Font.Style:=Canvas.Font.Style-[fsItalic];inc(i); end;
         'B':begin Canvas.Font.Style:=Canvas.Font.Style+[fsBold];inc(i); end;
         'b':begin Canvas.Font.Style:=Canvas.Font.Style-[fsBold];inc(i); end;
         '<':begin draw;inc(i); end;
         'c':
           begin
            scolor:=copy(s,i+2,8);
            try
             HexToBin(PChar(scolor),@color,4);
            except
             color:=0;
            end;
            Canvas.Font.Color:=color;  inc(i,10);
           end;
        end;
       end;
      inc(i);
    end;
   finally
    Canvas.Brush.Style:=bs;
   end;
  end;

 procedure AddLineToRichEdit(RichEdit:TRichEdit;s:string);
  type block=record _from,_to:integer; end;
  var Bold:array of block;
      Italic:array of block;
      Under:array of block;
      Clr:array of block;
      ClrVal:array of integer;
      ss:string;
      i,ii:integer;
      color:integer;
      scolor:string;
   procedure sel(f,t:integer);
    begin
     RichEdit.SelStart:=f;
     RichEdit.SelLength:=t-f+1;
    end;
  begin
   ss:='';ii:=0;i:=1;
   while i<=length(s) do
    begin
      if (s[i]<>'<')and(s[i]<>'{') then
       begin
        ss:=ss+s[i];inc(ii);inc(i);
       end else
       begin
//---------------------------------
        inc(i);
        case s[i] of
         'I':begin SetLength(Italic,length(Italic)+1);Italic[length(Italic)-1]._from:=ii+1;Italic[length(Italic)-1]._to:=-1;inc(i,2); end;
         'i':begin if(length(Italic)>0)then Italic[length(Italic)-1]._to:=ii;inc(i,2); end;
         'U':begin SetLength(Under,length(Under)+1);Under[length(Under)-1]._from:=ii+1;Under[length(Under)-1]._to:=-1;inc(i,2); end;
         'u':begin if(length(Under)>0)then Under[length(Under)-1]._to:=ii;inc(i,2); end;
         'B':begin SetLength(Bold,length(Bold)+1);Bold[length(Bold)-1]._from:=ii+1;Bold[length(Bold)-1]._to:=-1;inc(i,2); end;
         'b':begin if(length(Bold)>0)then Bold[length(Bold)-1]._to:=ii;inc(i,2); end;
         '<','{':begin ss:=ss+s[i];inc(ii);inc(i,2); end;
         'c':
           begin
            scolor:=copy(s,i+8,2)+copy(s,i+6,2)+copy(s,i+4,2)+copy(s,i+2,2);
            try
             HexToBin(PChar(scolor),@color,4);
            except
             color:=128;
            end;
             SetLength(Clr,length(Clr)+1);Clr[length(Clr)-1]._from:=ii+1;Clr[length(Clr)-1]._to:=-1;
             SetLength(ClrVal,length(ClrVal)+1);ClrVal[length(ClrVal)-1]:=color;
             inc(i,11);
           end;
        end;
//---------------------------------
       end;
    end;
   for i:=0 to length(Italic)-1 do if Italic[i]._to=-1  then Italic[i]._to:=ii;
   for i:=0 to length(Under)-1 do if Under[i]._to=-1  then Under[i]._to:=ii;
   for i:=0 to length(Bold)-1 do if Bold[i]._to=-1  then Bold[i]._to:=ii;
   for i:=0 to length(Clr)-1 do if Clr[i]._to=-1  then Clr[i]._to:=ii;
   RichEdit.Lines.Add(ss);

   ii:=length(RichEdit.Lines.text)-ii-3;
   for i:=0 to length(Italic)-1 do
    begin
     sel(Italic[i]._from+ii,Italic[i]._to+ii);
     RichEdit.SelAttributes.Style:=RichEdit.SelAttributes.Style + [fsItalic];
    end;
   for i:=0 to length(Bold)-1 do
    begin
     sel(Bold[i]._from+ii,Bold[i]._to+ii);
     RichEdit.SelAttributes.Style:=RichEdit.SelAttributes.Style + [fsBold];
    end;
   for i:=0 to length(Under)-1 do
    begin
     sel(Under[i]._from+ii,Under[i]._to+ii);
     RichEdit.SelAttributes.Style:=RichEdit.SelAttributes.Style + [fsUnderline];
    end;
   for i:=0 to length(Clr)-1 do
    begin
     sel(Clr[i]._from+ii,Clr[i]._to+ii);
     RichEdit.SelAttributes.Color:=ClrVal[i];
    end;

   for i:=0 to RichEdit.Lines.Count-2 do
     SendMessage(RichEdit.Handle,WM_VSCROLL,1,0);
   SendMessage(RichEdit.Handle,WM_VSCROLL,0,1);     
   sel(Length(RichEdit.Lines.Text),0);
//----------------------------------------
  end;
 function colorToStrR(i:integer):string;
  begin
   Result:='{c:'+IntToHex(i,8)+'}';
  end;
end.


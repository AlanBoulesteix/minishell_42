make v1
RES_B="result_bash"
RES_P="result_program"
INFILE="infile"
OUT_B="outfile_bash"
OUT_P="outfile_program"
touch $RES_B $RES_P $OUT_B $OUT_P
rm $RES_B
rm $RES_P
rm $OUT_B
rm $OUT_P
touch $RES_B $RES_P $OUT_B $OUT_P

./exec $INFILE $OUT_P > $RES_P
(ls < "$INFILE" ; echo a ; ls < "$INFILE" | cat | wc -l >> "$OUT_B" | grep ; echo b ; echo c | cat) >> $RES_B
(ls | cat | wc -l | grep) >> $RES_B
(ls | cat | grep e | wc -l) >> $RES_B


#compare
echo Outfiles :
diff $OUT_B $OUT_P
echo Result files :
diff $RES_B $RES_P

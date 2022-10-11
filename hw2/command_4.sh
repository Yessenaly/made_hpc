file=./Linux
if test -f "$file"; then
 echo "course"
 else
 echo "very easy"
 touch "$file"
fi
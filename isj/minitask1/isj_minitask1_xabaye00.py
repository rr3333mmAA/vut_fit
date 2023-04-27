# minitask 1
# modify the regular expression below so that
# it captures any string inside each <...>
# expected output ['/note', 'b', '/b', 'i', '/i']
import re
text = '</note> and <b>foo</b> and <i>so on</i> and 1 < 2'
matches = re.findall(r'<.+?>',text)
parsed_matches = []
for match[1] in matches:
    match = re.sub('<', '', match)
    match = re.sub('>', '', match)
    parsed_matches.append(match)
print(parsed_matches)

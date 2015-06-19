# get the Urania version from the script path
abspath = os.path.abspath(os.path.dirname(__file__))
rematch = re.search('.Urania_(?P<ver>v\d+r\d+p?\d?).', abspath)
ver=rematch.group('ver')



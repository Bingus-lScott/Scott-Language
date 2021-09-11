from universal_imports import *

###################
# LEXER
###################

class Lexer:
	def __init__(self, fn, text):
		self.fn = fn
		self.text = text
		self.pos = Position(-1, 0, -1, fn, text)
		self.current_char = None
		self.advanceChar()
	
	# Advances the read position
	# This advanceChar defines it
	def advanceChar(self):
		self.pos.advance(self.current_char)
		self.current_char = self.text[self.pos.idx] if self.pos.idx < len(self.text) else None

	# Writes tokens to a list/array
	def make_tokens(self):
		tokens = []

		# Token/Number Writing logic
		while self.current_char != None:
			if self.current_char in ' \t':
				self.advanceChar()
			elif self.current_char in DIGITS:
				tokens.append(self.make_number())
			elif self.current_char == '+':
				tokens.append(Token(TT_PLUS, pos_start=self.pos))
				self.advanceChar()
			elif self.current_char == '-':
				tokens.append(Token(TT_MINUS, pos_start=self.pos))
				self.advanceChar()
			elif self.current_char == '*':
				tokens.append(Token(TT_MUL, pos_start=self.pos))
				self.advanceChar()
			elif self.current_char == '/':
				tokens.append(Token(TT_DIV, pos_start=self.pos))
				self.advanceChar()
			elif self.current_char == '(':
				tokens.append(Token(TT_LPAREN, pos_start=self.pos))
				self.advanceChar()
			elif self.current_char == ')':
				tokens.append(Token(TT_RPAREN, pos_start=self.pos))
				self.advanceChar()
			else:
				pos_start = self.pos.copy()
				char = self.current_char
				self.advanceChar()
				return [], IllegalCharError(pos_start, self.pos, "'" + char + "'")
		# Checks if read position is at end of file
		tokens.append(Token(TT_EOF, pos_start=self.pos))
		return tokens, None

	# Adds number to token list/array
	def make_number(self):
		num_str = ''
		dot_count = 0
		pos_start = self.pos.copy()

		# Decimal logic
		while self.current_char != None and self.current_char in DIGITS + '.':
			if self.current_char == '.':
				if dot_count == 1: break
				dot_count += 1
				num_str += '.'
			else:
				num_str += self.current_char
			self.advanceChar()

		if dot_count == 0:
			return Token(TT_INT, int(num_str), pos_start, self.pos)
		else:
			return Token(TT_FLOAT, float(num_str), pos_start, self.pos)
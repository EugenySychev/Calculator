package org.sychev.calculator

import kotlin.math.*

class CalcEngine {
    var isDegMode: Boolean = false

    fun calculate(expression: String): Double {
        val normalized = expression.replace(",", ".").replace(" ", "")
        return Parser(normalized, isDegMode).parse()
    }

    private class Parser(private val input: String, private val degMode: Boolean) {
        private var pos = 0

        fun parse(): Double {
            if (input.isEmpty()) throw IllegalArgumentException("Empty expression")
            val result = parseAddSub()
            if (pos != input.length) throw IllegalArgumentException("Unexpected '${input[pos]}' at $pos")
            return result
        }

        private fun toRad(a: Double) = if (degMode) Math.toRadians(a) else a
        private fun fromRad(a: Double) = if (degMode) Math.toDegrees(a) else a

        private fun parseAddSub(): Double {
            var result = parseMulDiv()
            while (pos < input.length) {
                val op = input[pos]
                if (op != '+' && op != '-') break
                pos++
                val right = parseMulDiv()
                result = if (op == '+') result + right else result - right
            }
            return result
        }

        private fun parseMulDiv(): Double {
            var result = parsePower()
            while (pos < input.length) {
                when {
                    input[pos] == '*' -> { pos++; result *= parsePower() }
                    input[pos] == '/' -> { pos++; result /= parsePower() }
                    input.startsWith("mod", pos) -> { pos += 3; result %= parsePower() }
                    else -> break
                }
            }
            return result
        }

        private fun parsePower(): Double {
            val base = parseUnary()
            return if (pos < input.length && input[pos] == '^') {
                pos++
                base.pow(parseUnary())
            } else base
        }

        private fun parseUnary(): Double {
            if (pos < input.length && input[pos] == '-') { pos++; return -parsePostfix() }
            if (pos < input.length && input[pos] == '+') { pos++ }
            return parsePostfix()
        }

        private fun parsePostfix(): Double {
            var value = parsePrimary()
            while (pos < input.length) {
                when (input[pos]) {
                    '!' -> { pos++; value = factorial(value) }
                    '%' -> { pos++; value /= 100.0 }
                    else -> break
                }
            }
            return value
        }

        private fun parsePrimary(): Double {
            if (pos >= input.length) throw IllegalArgumentException("Unexpected end of expression")
            val ch = input[pos]

            if (ch == '(') {
                pos++
                val value = parseAddSub()
                consume(')')
                return value
            }

            if (ch == '|') {
                pos++
                val value = parseAddSub()
                consume('|')
                return abs(value)
            }

            if (ch == 'π') { pos++; return PI }

            // Functions — longest match first to avoid sin matching asin
            val functions = listOf("asin", "acos", "atan", "sin", "cos", "tan", "log", "ln", "√")
            for (fn in functions) {
                if (input.startsWith(fn, pos)) {
                    pos += fn.length
                    consume('(')
                    val arg = parseAddSub()
                    consume(')')
                    return applyFunction(fn, arg)
                }
            }

            // e constant — only when not followed by digit (scientific notation handled in parseNumber)
            if (ch == 'e' && (pos + 1 >= input.length || (!input[pos + 1].isDigit() && input[pos + 1] != '.'))) {
                pos++
                return E
            }

            if (ch.isDigit() || ch == '.') return parseNumber()

            throw IllegalArgumentException("Unexpected '$ch' at position $pos")
        }

        private fun parseNumber(): Double {
            val start = pos
            while (pos < input.length && (input[pos].isDigit() || input[pos] == '.')) pos++
            // Scientific notation: e+10, e-10, e10
            if (pos < input.length && input[pos] == 'e') {
                val next = pos + 1
                if (next < input.length && (input[next].isDigit() || input[next] == '+' || input[next] == '-')) {
                    pos++
                    if (input[pos] == '+' || input[pos] == '-') pos++
                    while (pos < input.length && input[pos].isDigit()) pos++
                }
            }
            return input.substring(start, pos).toDouble()
        }

        private fun consume(c: Char) {
            if (pos >= input.length || input[pos] != c) throw IllegalArgumentException("Expected '$c'")
            pos++
        }

        private fun applyFunction(name: String, arg: Double): Double = when (name) {
            "sin" -> sin(toRad(arg))
            "cos" -> cos(toRad(arg))
            "tan" -> tan(toRad(arg))
            "asin" -> fromRad(asin(arg))
            "acos" -> fromRad(acos(arg))
            "atan" -> fromRad(atan(arg))
            "log" -> log10(arg)
            "ln" -> ln(arg)
            "√" -> sqrt(arg)
            else -> throw IllegalArgumentException("Unknown function: $name")
        }

        private fun factorial(n: Double): Double {
            if (n < 0 || n != floor(n)) throw ArithmeticException("Factorial requires non-negative integer")
            if (n > 20) throw ArithmeticException("Factorial overflow")
            var result = 1.0
            for (i in 1..n.toInt()) result *= i
            return result
        }
    }
}

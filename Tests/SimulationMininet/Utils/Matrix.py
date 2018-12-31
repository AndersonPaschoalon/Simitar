
class Matrix(object):
    @staticmethod
    def column(matrix, i):
        """
        Returns a column of a two dimensional matrix
        mtr_col = column(mtr, 2):
        :param matrix: matrix
        :param i: column index
        :return: vector
        """
        return [row[i] for row in matrix]

    @staticmethod
    def _test_column():
        m = [['abacaxi', '3', '5', '6', '7', '7'], ['banana', '0', '4', '5', '6', '7'],
             ['caqui', '1', '3', '4', '5', '6'], ['damasco', '7', '14', '15', '16', '17'],
             ['damasco', '7', '14', '15', '16', '17'], ['caqui', '7', '14', '15', '16', '17'],
             ['figo', '2', '99', '98', '97', '96'], ['goiaba', '9', '10', '11', '12', '13']]
        col0 = Matrix.column(m, 0)
        print(col0)

    @staticmethod
    def order_matrix(mtr, n_column):
        """
        Order the matrix according to the column n
        m_ordered = order_matrix(m, 1)
        :param mtr:
        :param n_column:
        :return:
        """
        mtr = sorted(mtr, key=lambda mtr: float(mtr[n_column]))
        return mtr

    @staticmethod
    def _test_order_matrix():
        m = [['abacaxi', '3', '5', '6', '7', '7'], ['banana', '0', '4', '5', '6', '7'],
             ['caqui', '1', '3', '4', '5', '6'], ['damasco', '7', '14', '15', '16', '17'],
             ['damasco', '7', '14', '15', '16', '17'], ['caqui', '7', '14', '15', '16', '17'],
             ['figo', '2', '99', '98', '97', '96'], ['goiaba', '9', '10', '11', '12', '13']]
        m_ordered = Matrix.order_matrix(m, 1)
        print(m_ordered)

    @staticmethod
    def order_matrix_str(mtr, n_column):
        """
        Order the matrix according to the column n
        m_ordered = order_matrix(m, 1)
        :param mtr:
        :param n_column:
        :return:
        """
        col_str = sorted(Matrix.column(mtr, n_column))
        mtr_out = []
        for i in range(0, len(col_str)):
            for j in range(0, len(col_str)):
                if mtr[j][n_column] == col_str[i]:
                    mtr_out.append(mtr[j])
        return mtr_out

    @staticmethod
    def _test_order_matrix_str():
        mtr = [['pera', '1', '2', '3'], ['uva', '3', '4', '5'],
               ['abacaxi', '7', '6', '5'], ['banana', 'd', 'f', 'g']]
        mtr = Matrix.order_matrix_str(mtr, 0)
        print(mtr)

    @staticmethod
    def get_mtr_position(mtr, model):
        """
        Return the position(line) of the model(first column of a matrix)
        :param mtr:
        :param model:
        :return:
        """
        pos = -1
        for i in range(0, len(mtr)):
            if model == mtr[i][0]:
                pos = i
                break
        return pos

    @staticmethod
    def _test_get_mtr_position():
        """
        #
        :return:
        """
        m = [['banana', '0', '4', '5', '6', '7'],
             ['caqui', '1', '3', '4', '5', '6'],
             ['figo', '2', '99', '98', '97', '96'],
             ['abacaxi', '3', '5', '6', '7', '7'],
             ['damasco', '7', '14', '15', '16', '17'],
             ['goiaba', '9', '10', '11', '12', '13']]
        pos = Matrix.get_mtr_position(m, 'damasco')
        print('pos=' + str(pos))

if __name__ == "__main__":
    Matrix._test_column()
    Matrix._test_order_matrix()
    Matrix._test_order_matrix_str()
    Matrix._test_get_mtr_position()
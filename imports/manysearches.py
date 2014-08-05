from imports import globals


class MuchSearch(object):
    def __init__(self):
        self.array = []

    def sort(self, array, column, value):
        i=0
        m=[]
        for each in array:
            if array[i][column] == value:
                m.append(each)
            i += 1
        return m

    def PrintPayloads(self, m):
        '''
        :todo: Need to get this function much smaller.
        apparently i was way too sleepy to write code...
        :param m: Array to print out
        :return:nothing
        '''
        print "\nPayloads Found:"
        array = m
        i = 0
        print "ID\tVIP\tType\t\tLang\tArch\tPlat\tName"
        print '---\t---\t-----\t\t-----\t----\t-----\t----------------'
        for element in array:
            answer = array[i][globals.vars.column_for_uid]
            answer = array[i][globals.vars.column_for_vip]
            answer += '\t%s' % ('{0: <12}'.format(array[i][globals.vars.column_for_type]))
            answer += '\t%s' % ('{0: <12}'.format(array[i][globals.vars.column_for_pl]))
            answer += array[i][globals.vars.column_for_arch] + '\t'
            answer += array[i][globals.vars.column_for_plat] + '\t'
            answer += '\t%s' % ('{0: <12}'.format(array[i][globals.vars.column_for_name]))
            print answer
            i += 1

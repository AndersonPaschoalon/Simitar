from fnvhash import fnv1a_32
import collections

class OrderedSet(collections.MutableSet):

    def __init__(self, iterable=None):
        self.end = end = []
        end += [None, end, end]         # sentinel node for doubly linked list
        self.map = {}                   # key --> [key, prev, next]
        if iterable is not None:
            self |= iterable

    def __len__(self):
        return len(self.map)

    def __contains__(self, key):
        return key in self.map

    def add(self, key):
        if key not in self.map:
            end = self.end
            curr = end[1]
            curr[2] = end[1] = self.map[key] = [key, curr, end]

    def discard(self, key):
        if key in self.map:
            key, prev, next = self.map.pop(key)
            prev[2] = next
            next[1] = prev

    def __iter__(self):
        end = self.end
        curr = end[2]
        while curr is not end:
            yield curr[0]
            curr = curr[2]

    def __reversed__(self):
        end = self.end
        curr = end[1]
        while curr is not end:
            yield curr[0]
            curr = curr[1]

    def pop(self, last=True):
        if not self:
            raise KeyError('set is empty')
        key = self.end[1][0] if last else self.end[2][0]
        self.discard(key)
        return key

    def __repr__(self):
        if not self:
            return '%s()' % (self.__class__.__name__,)
        return '%s(%r)' % (self.__class__.__name__, list(self))

    def __eq__(self, other):
        if isinstance(other, OrderedSet):
            return len(self) == len(other) and list(self) == list(other)
        return set(self) == set(other)

class IndexOrderedSet(OrderedSet):
    def index(self, elem):
        if elem in self.map:
            return next(i for i, e in enumerate(self) if e == elem)
        else:
            raise KeyError("That element isn't in the set")


class FlowId:
    def __init__(self):
        self._flowCounter = 0;
        self._set_flow_hashes = IndexOrderedSet();

    def getNumberOfFlows(self, flow_string):
        '''
        Adds a new flow to the flow-list, and returns the current number of registred flows
        :param flow_string: concatenation of ether_type|ip_src|ip_dst|ip_proto|src_port|dst_port
        :return: current number of flows
        '''
        flow_hash = fnv1a_32(bytes(flow_string, 'ascii'))
        self._set_flow_hashes.add(flow_hash);
        return len(self._set_flow_hashes)

    def getNumberOfFlows(self):
        return len(self._set_flow_hashes)

    def getFlowId(self, flow_string):
        """
        flowId return the flowID of a packet string flow identifier.

        :param flow_string: concatenation of ether_type|ip_src|ip_dst|ip_proto|src_port|dst_port
        :return:
        """
        flow_hash = fnv1a_32(bytes(flow_string, 'ascii'))
        self._set_flow_hashes.add(flow_hash);
        return self._set_flow_hashes.index(flow_hash)


'''
a = IndexOrderedSet()
flow_calc = FlowId()
s1 = "banana"
s2 = "pera"
s3 = "carambola"
s4 = "carambola"
s5 = "banana"
s6 = "pera"
s7 = "carambola"
s8 = "carambola"
s9 = "tuti-fruti"
s1_id = flow_calc.getFlowId(s1)
s2_id = flow_calc.getFlowId(s2)
s3_id = flow_calc.getFlowId(s3)
s4_id = flow_calc.getFlowId(s4)
s5_id = flow_calc.getFlowId(s5)
s6_id = flow_calc.getFlowId(s6)
s7_id = flow_calc.getFlowId(s7)
s8_id = flow_calc.getFlowId(s8)
s9_id = flow_calc.getFlowId(s9)
print("s1 = ", s1, ", s1_id = ", s1_id)
print("s2 = ", s2, ", s2_id = ", s2_id)
print("s3 = ", s3, ", s3_id = ", s3_id)
print("s4 = ", s4, ", s4_id = ", s4_id)
print("s5 = ", s5, ", s5_id = ", s5_id)
print("s6 = ", s6, ", s6_id = ", s6_id)
print("s7 = ", s7, ", s7_id = ", s7_id)
print("s8 = ", s8, ", s8_id = ", s8_id)
print("s9 = ", s9, ", s9_id = ", s9_id)
'''